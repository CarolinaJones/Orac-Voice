# Using ORAC-VOICE with cool-retro-term


**Create an app that runs ORAC-VOICE within cool-retro-term, as an application.**

- This uses a combination of cool-retro-term and Apple's Automator app.
- There is a need to authorize Personal voice, with cool-retro-term and the newly created app. 

**1. Download and install cool-retro-term to Application:**

There currently seems to be a bug with the most recent versions of this app, preventing it from starting in full screen. If that doesn't matter to you, grab the latest version.

I recommend version 1.20 for this project.
```bash
https://github.com/Swordfish90/cool-retro-term/releases
````
When you try and run cool-retro-term, you'll get a message saying it can't be run. Go into `Privacy and Security` in `Settings` and choose `run anyway` and authorize.

**2. Create the app in Automator:**

Open `AUTOMATOR` and select `Application` as a template. Search for `Run Shell Script` on the top left and select. Paste in the code from one of these options: (it is assuming your default location of orac-voice.. Change as necessary.)

- 1. This will start cool-retro-term, initiate the VENV and start the chat in full screen. 
*(This version does not exit cool-retro-term when quitting ORAC-VOICE, which is very important as we need the shell, to drop in some code to authorize, Personal Voice.)*
````bash
/Applications/cool-retro-term.app/Contents/MacOS/cool-retro-term -T "ORAC Mainframe" --workdir ~/orac-voice --fullscreen -e bash --rcfile <(echo "source orac-venv/bin/activate && python3 orac_chat.py")
````
You can test it by using the `run` button in Automator. When you're happy, save the application to the desktop.

**2. Start the App and authorize Personal Voice:**

Open your new app and all being well, ORAC will come to life. `CTRL+C` to exit the UI and you will be at the shell window. Paste in the following code and press `RETURN`. *(You should get an authorization pop-up from Apple, which you will need to agree.)*
````bash
echo '#import <AVFoundation/AVFoundation.h>
int main(){ 
[AVSpeechSynthesizer requestPersonalVoiceAuthorizationWithCompletionHandler:^(AVSpeechSynthesisPersonalVoiceAuthorizationStatus status){ 
printf("Status: %ld\\n", (long)status); }]; 
[[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:2.0]]; 
return 0; }' > auth_check.m && gcc -framework AVFoundation -framework Foundation auth_check.m -o auth_check && ./auth_check
````
Type `EXIT` to leave cool-retro-pro. You should now be able to open you newly created app and have it work with Personal Voice. *(You may also receive a pop-up to authorize microphone access to the app.)*

- 2. This version of the script code is slightly different and will allow cool-retro-term to fully close, when you exit the ORAC UI. *(The problem with this, is not being able to run the authorization code for Personal Voice, meaning this will only work with SIRI and Synth Voices.)*
````bash
/Applications/cool-retro-term.app/Contents/MacOS/cool-retro-term -T "ORAC Mainframe" --workdir ~/orac-voice -e bash -c "source orac-venv/bin/activate && python3 orac_chat.py"
````

**It's important to note that you may need to alter the paths to suit the location of your ORAC-VOICE base directory. By default, it will work if you base directory is in your home name and orac-voice. (~/orac-voice)**

Good luck! :-)

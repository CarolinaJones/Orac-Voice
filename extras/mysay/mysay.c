#import <AVFoundation/AVFoundation.h>

int main(){
  [AVSpeechSynthesizer requestPersonalVoiceAuthorizationWithCompletionHandler:^(AVSpeechSynthesisPersonalVoiceAuthorizationStatus status){
     // authorization popup should be visible now
  }];
  [[NSRunLoop currentRunLoop] run];
  return 0;
}
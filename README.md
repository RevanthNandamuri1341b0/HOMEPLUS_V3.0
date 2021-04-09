# HOME+ v3.0 
This is a better verion than HOME+ v2.0.A third party application is used to create a perfect M2M communication.

## ARDUINO IDE
* [DOWNLOAD IDE](https://www.arduino.cc/en/Main.Software)
* Preferences--> Aditional boards Manager URLs : [LINK1](https://dl.espressif.com/dl/package_esp32_index.json) | [LINK2](http://arduino.esp8266.com/stable/package_esp8266com_index.json)
* Download boards:-
  * [ESP8266 NodeMCU](https://github.com/esp8266/Arduino)
  * [ESP32NodeMCU](https://github.com/espressif/arduino-esp32)

## NodeMCU
* [Brought from amazon](https://www.amazon.in/Lolin-NodeMCU-ESP8266-CP2102-Wireless/dp/B010O1G1ES/ref=sr_1_2?dchild=1&keywords=nodeMCU&qid=1614248056&sr=8-2) 


## Sinric
This 3rd party application has enhanced the M2M communication between Alexa and Microrontroller.
Create an account to setup and generate API keys for communicating with NodeMCU
Register or Login from
* [Sinric.com](https://sinric.com/login?returnUrl=%2F)
* [Android](https://play.google.com/store/apps/details?id=com.sinric)
DeviceId is the ID assgined to your smart-home-device in sinric.com dashboard. Copy it from dashboard and paste it inside the code

#### For Switch or Light device types
```{"deviceId": xxxx, "action": "setPowerState", value: "ON"}```

check [developer amazon](https://developer.amazon.com/docs/device-apis/alexa-powercontroller.html) for more information 

If you are going to use a push button to on/off the switch manually,use this function to update the status on the server so it will reflect on Alexa app.

```setPowerStateOnServer("deviceid", "ON")```



## Alexa Configuration 
You can configure your devices from below links:-
* [Alexa App on Windows PC](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwjxqJj28obvAhUDxzgGHWH2DiAQFjAAegQIAxAD&url=https%3A%2F%2Fwww.microsoft.com%2Fen-us%2Fp%2Falexa%2F9n12z3cctcnz&usg=AOvVaw1x8YklTHNuEhsD3HnCG8B8)
* [Alexa on Android](https://www.google.com/search?client=ms-android-oppo&sxsrf=ALeKk03yH_F9JaM_WkrfkGDSYUDlh3FKZg%3A1614320272534&ei=kJI4YJWRIJOC4-EPq4WZgAE&q=alexa+app&oq=alexa+app&gs_lcp=ChNtb2JpbGUtZ3dzLXdpei1zZXJwEAMyBQgAEJECMggIABCxAxCRAjICCAAyAggAMgIIADICCAAyAggAMgIIADoECAAQRzoECCMQJzoLCAAQsQMQyQMQkQI6BQgAEJIDOgUIABCxAzoHCAAQhwIQFFDIMVi5N2DGOWgAcAF4AIABnAKIAd8GkgEFMC4yLjKYAQCgAQHIAQjAAQE&sclient=mobile-gws-wiz-serp#)
* [Alexa on IOS](https://apps.apple.com/us/app/amazon-alexa/id944011620)
* [Alexa Web](alexa.amazon.in)

After configuring your wifi and setting up the Devices ID, Dump The code in NodeMCU 
Then in The Alexa application, In *Browse Skills* search and add enable ***Sinric*** skill. 
In *Add Device*, Scan for **Other** Devices in the menu and wait for 45 seconds.
Alexa will automatically Detects 4 Switches. Make sure the Alexa application device(mobile/PC) and the NodeMCU must be on same network. If it still could not fine devices check your connectivity. 



## Controlled From
* [Alexa devices](https://www.amazon.in/s?i=amazon-devices&bbn=12621640031&rh=n%3A12621639031%2Cn%3A12805338031&dc&qid=1614319203&rnid=12621640031&ref=sr_nr_n_1) like Echo dot or Fire stick tv.
* [Alexa App on Windows PC](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwjxqJj28obvAhUDxzgGHWH2DiAQFjAAegQIAxAD&url=https%3A%2F%2Fwww.microsoft.com%2Fen-us%2Fp%2Falexa%2F9n12z3cctcnz&usg=AOvVaw1x8YklTHNuEhsD3HnCG8B8)
* [Alexa on Android](https://www.google.com/search?client=ms-android-oppo&sxsrf=ALeKk03yH_F9JaM_WkrfkGDSYUDlh3FKZg%3A1614320272534&ei=kJI4YJWRIJOC4-EPq4WZgAE&q=alexa+app&oq=alexa+app&gs_lcp=ChNtb2JpbGUtZ3dzLXdpei1zZXJwEAMyBQgAEJECMggIABCxAxCRAjICCAAyAggAMgIIADICCAAyAggAMgIIADoECAAQRzoECCMQJzoLCAAQsQMQyQMQkQI6BQgAEJIDOgUIABCxAzoHCAAQhwIQFFDIMVi5N2DGOWgAcAF4AIABnAKIAd8GkgEFMC4yLjKYAQCgAQHIAQjAAQE&sclient=mobile-gws-wiz-serp#)
* [Alexa on IOS](https://apps.apple.com/us/app/amazon-alexa/id944011620)

## DEMO VIDEO
[![HOME+ 3.0 DEMO](http://img.youtube.com/vi/7ApxwqBdxYQ/0.jpg)](http://www.youtube.com/watch?v=7ApxwqBdxYQ "HOME+ 3.0")
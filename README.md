third
=====
# Smile

Smile is a xcode written project with the c++ language that enables the color of the background to be changed according to the facial expression. 

It calculates the distance between the two ends of the inner mouth and if it is bigger than a certain value, then it considers it as a smile. It is also depending on the distance from the camera which was calculated using the nose size. 

if the nose size is smaller than 40, and then the mouth stretch is bigger than 50 then it is a smile, however, if the nose size is between 64 and 80 then the mouth stretch has to be > 80 to indicate a smile.
 
This could be used for many causes starting from simple user interface up to aiding people suffering Agnosia. 

Sources used: 
>Kyle Mcdonald

>https://github.com/kylemcdonald/openFrameworks

>https://github.com/kylemcdonald/ofxCv

>https://github.com/kylemcdonald/ofxFaceTracker

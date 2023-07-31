# Vboard

##Description
Vboard , as V suggest, is a virtual board which can be used to draw or write on the screen without having to interact with any of the devices. It detects object of specific colour and draws along wherever the object is headed. It can detect objects upto 1.5+ meter far.
---
###Instructions
Those specific colour has been hard coded for development reason:
Draw : Ligth neon green.
Pointer : Dark blue.
Object Detection algorithm uses HSV color model to detect the object of these colours :
1. For Draw : 
    * Hue-min : 27
    * Hue-max : 80
    * Saturation-min : 49
    * Saturation-max : 191
    * Value-min : 145
    * Value-max : 251

2. For Pointer : 
     * Hue-min : 106
     * Hue-max : 124
     * Saturation-min : 126
     * Saturation-max : 213
     * Value-min : 89
     * Value-max : 149
---
## Link to the live demo
[Vboard live demo](https://youtu.be/HPwnpdTzNog)

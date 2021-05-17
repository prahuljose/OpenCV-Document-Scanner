# An OpenCV based document scanner
## Built entirely on visual studio in C++, time taken: 3 days.
</br>

You can find the link to the C++ file [here](https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/Document-Scanner.cpp)

## Results:
|Index|Original Image|Contoured|Perspective Warp|Final Cropped|
|:----:|:----:|:----:|:----:|:----:|
|1|<img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/one.jpg" width="150" height="300" />| <img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/one_contour.png" width="150" height="300" />  |<img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/one_warp.png" width="200" height="300" />     | <img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/one_crop.png" width="200" height="300" />  </br> |
|2|<img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/two.jpg" width="250" height="250" />| <img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/two_contour.png" width="250" height="275" />  |<img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/two_warp.png" width="175" height="225" />     | <img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/two_crop.png" width="175" height="225" />  </br> |
|3|<img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/three.jpg" width="250" height="250" />| <img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/three_contour.png" width="250" height="275" />  |<img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/three_warp.png" width="175" height="225" />     | <img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/three_crop.png" width="175" height="225" />  </br> |
|4|<img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/four.jpg" width="250" height="300" />| <img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/four_contour.png" width="250" height="300" />  |<img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/four_warp.png" width="250" height="300" />     | <img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/four_crop.png" width="250" height="300" />  </br> |
</br>

</br>

## Process
--> Reading image file to a matrix data type.
</br>
<img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/1.png" width="600" height="100" />

--> Preprocessing includes converting the input image to grayscale and blurring it a little bit. We then use Canny edge detection to detect the evident edges. And finally using a defined kernel size, we dilate the image a little bit.
</br>
<img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/2.png" width="688" height="242" />

--> We then proceed to find the contours in the dilated image; along with this we approximate the number of edges of the contour to classify it into the required polygon. We filter out all contours except the biggest, which should be the required document needed to be scanned. And return the points where this contours exist back to the MAIN function.
</br>
<img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/3.png" width="1178" height="795" />

--> The next step would be to reorder our points, in order to do this we can observe that in a 4 vertices object in the 2d space, if we find the sum of the x cordinate and its y cordinate for all points separately, the highest value will be the point at the BOTTOM RIGHT, and the lowest value will be the point at the TOP LEFT. Similarly, if we find the difference of the x cordinate and its y cordinate for all points separately, the highest value will be the point at the TOP RIGHT, and the lowest value will be the point at the BOTTOM LEFT.
</br>
<img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/4.png" width="462" height="75" />
</br>
<img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/5.png" width="990" height="400" />
</br>
We use the above logic to correctly reorder the vertices correctly as to avoid any future error in the perspective warp phase.

--> The next and final step is to warp the perspective of the image, using an inbuilt function in OpenCV.
</br>
<img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/6.png" width="660" height="200" />


--> Another step which i implemented is to slightly crop the image, using an inset of 10 points on all edges of the final image. For better clarity.
</br>
<img src="https://github.com/prahuljose/OpenCV-Document-Scanner/blob/main/ExtraFiles/7.png" width="713" height="82" />

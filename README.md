# zixunToyRayTracer
## my toyRayTracer

In this project I followed awsome resources from [Quantitve Bytes](https://www.youtube.com/@QuantitativeBytes)  
and do everthing from scratch after watching it(not copying/ pasting, but write in my own way).
I plan to add some new algorithms after finishing the basic framework of this;

If one want use this project, they should simply use make command , and make clean to clean all unnecessary object files


# milestone 1:     <br>
1.camera and raycasting with pixels <br>
2. mutiple objects (interface&&shared_ptr_list) <br>
3. multiple lights (interface&&shared_ptr_list) <br>
4. sphere geometry intersection test and basic light(Lambertian Shading Model) <br>
5. Improvements over the [Quantitve Bytes](https://www.youtube.com/@QuantitativeBytes) :<br>
change the intensity into the Lambertian Shading model in [1] <br>
<img width="696" alt="image" src="https://user-images.githubusercontent.com/116760304/212446133-f4232fb9-fd3a-42ae-b296-b22878560a47.png"> <br>
pic1 from [1] <br>
<img width="717" alt="46ea9966145a5c05d41466262db2f2a" src="https://user-images.githubusercontent.com/116760304/212210644-e3316746-80ec-4bb3-b7e0-adea3b63c4b4.png">


# milestone 2: <br>
1. add transformation
2. transformation from local coord to wolrd coord
3. add some sphere
<img width="856" alt="image" src="https://user-images.githubusercontent.com/116760304/212377648-873471d2-fc08-49f9-9305-48c905cec082.png">

# milestone 3: <br>
1. add a plane
2. rewrite the scene and intersection
3. add shadow check in compute illuminations
4. add 2 more test light(one blue and another red)
5. add phong  specular highlights model
<img width="935" alt="image" src="https://user-images.githubusercontent.com/116760304/212521567-f7c6a509-69ae-4e8d-940f-4494fe12f0b9.png">
<img width="917" alt="image" src="https://user-images.githubusercontent.com/116760304/212576723-1234e8ae-7091-49fa-9c11-ee92facace04.png">
<img width="835" alt="2831093a5fd8e3803f1c89116a693f3" src="https://user-images.githubusercontent.com/116760304/212584605-8cbc68bf-065a-4154-b2a0-ef6bef8127f6.png">

#milestone 4: <br>
1. add recursive reflection
<img width="953" alt="image" src="https://user-images.githubusercontent.com/116760304/212771913-5eb7466b-529d-4772-a210-8440f64b3ba8.png">


## reference
[1] Real-Time Rendering, Fourth Edition 4th Edition
by Eric Haines  (Author), Naty Hoffman (Author), Tomas Akenine-Mo??ller (Author) <br>
[2] Fundamentals of Computer Graphics 4th Edition
by Steve Marschner (Author), Peter Shirley (Author) <br>
[3] (Strongly suggested) Physically Based Rendering, fourth edition: From Theory to Implementation 4th Edition
by Matt Pharr (Author), Wenzel Jakob (Author), Greg Humphreys (Author) <br>

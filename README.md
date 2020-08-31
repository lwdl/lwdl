### Light Weight Data Language
Light Weight Data Language is a language used for storing data, for ease of use.

I created this data language, as I wanted something that I could use without compiling the whole application.

Orginally, this project was suppose to be close sourced, but as I kept working on it. I felt like LWDL, could help other people aswell.





### What is it? 
LWDL is a data language written in C, natively working with C++.

LWDL, was created to allow people to not re-compile the application if they would've changed a variable.

### Orgin:
LWDL was orginally called JDATA. JDATA has been written but it exists as a C++ program.

JDATA was completed, but due to some issues. I decided to write JDATA as a C file.

### What can it support? 
  LWDL can support:
  
  - ints
  
  - doubles
  
  - strings
  
  - characters
  
  - functions
  
  - floats
  
 
### LWDL code.
```
list person {
  Name : Jake
  Age : 14
  Animation : @playingBasketBall

}
```
We create a object named Person, within that Person Object, we set variables within the object.

Variables being, a string, age , and a function.

the @ key is used to tell the parser, that the object is a void type. 

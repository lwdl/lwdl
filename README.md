### Light Weight Data Language
Light Weight Data Language is a language used for storing data, for ease of use.

I created this data language, as I wanted something that I could use without compiling the whole application.

Orginally, this project was suppose to be close sourced, but as I kept working on it. I felt like LWDL, could help other people aswell.





### What is it? 
LWDL is a data language written in C, and a verison within C++

LWDL, was created to allow people to not re-compile the application if they would've changed a variable.

### Orgin:
LWDL was orginally called JDATA. JDATA has been written but it exists as a C++ program, and JDATA was slow. 

### What can it support? 
  LWDL can support:
  
  - ints
  
  - doubles
  
  - words
  
  - characters
  
  - floats
  
 
### LWDL code.
```js
list UI
{
  Label : Color
  ColorPallet : 1
  DebugProfile : 1
  view_type : VIEW_TYPE_SMOOTH
}

list Player
{

  a_dash : 1
  a_combos : 1
  a_dead_when_key_pressed : 0
  debugging_mode : 1
  

}

```
We create a object named Person, within that Person Object, we set variables within the object.

Variables being, a words, and a int.


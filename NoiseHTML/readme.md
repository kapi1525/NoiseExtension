## Noise html port


## FastNoiseLite

FastNoiseLite was modied to make it work with old version of closure compiler used by clickteam.
patch is in ./patches/, its applied by npm install
What was changed:
- Moved all FastNoiseLite class member variables to its constructor where they are created using this.var_name syntax
- All static functions and member variables were moved outside FastNoiseLite class and are initialized using old syntax supported by closure.
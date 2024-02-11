## Noise html port quirks

- Generated noise values are very simmilar but not the same. The difference is very small, almost always less than 0.000001, but its there.
  This is because JS uses 64bit double precsision floating-point numbers in calculations but c++ version uses 32bit single precission.
- Surface object integration is *currently* not supported. Not sure if porting it is possible.


## Buidling

- Run `npm install` to install dependencies and apply FastNoiseLite patch located in ./patches/.
- Run `npm run build` to combine all source files into one, ./dist/Noise.js.


## FastNoiseLite

FastNoiseLite was modied to make it work with old version of closure compiler used by clickteam.
Patch located in "./patches/" is applied during npm install.
What was changed:
- Moved all FastNoiseLite class member variables to its constructor where they are created using this.var_name syntax
- All static functions and member variables were moved outside FastNoiseLite class and are initialized using old syntax supported by closure.
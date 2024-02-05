## Noise html port


## FastNoiseLite

FastNoiseLite was modied to make it work with old version of closure compiler used by clickteam.
patch is in ./patches/, its applied by npm install
What was changed:
- Moved all member variables to FastNoiseLite class constructor and all of them are accessed using `this`.
- References inside the library to `FastNoiseLite` class were repleaced with `this` for example: `FastNoiseLite.NoiseType.OpenSimplex2` was repleaced by `this.NoiseType.OpenSimplex2`.
- Outside the library to accessing constants use `<FastNoiseLite class instance here>.NoiseType.OpenSimplex2`.
const path = require('path');

module.exports = {
    entry: './Noise.js',
    output: {
        filename: 'Noise.js',
        path: path.resolve(__dirname, 'dist'),
        library: {
            // Export default as a var with CRunNoise name
            name: 'CRunNoise',
            type: 'var',
            export: 'default',
        },
    },
    target: ['web', 'es3'],
    mode: 'development',      // Mode production is broken but thats fine, closure will minify everything.
    devtool: false,
};
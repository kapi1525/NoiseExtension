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
    resolve: {
        alias: {
            // TODO: Make this chose the correct sdk if targeting html or uwp
            DarkEdif$: path.resolve(__dirname, 'DarkEdif.html.js'),
        },
    },
    optimization: {
        minimize: false,
    },
    target: 'web',
    mode: 'development',
    devtool: false,
};
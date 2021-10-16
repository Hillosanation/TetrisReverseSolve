const { decoder, Field } = require('tetris-fumen');
var args = process.argv.slice(2);
console.log(decoder.decode(args[0]));
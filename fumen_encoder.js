const { encoder, Field } = require('tetris-fumen');

function encode(InputField) {
	const pages = [];
	// pages.push({
	//     field: Field.create(
	//         'XXX_______' +
	//         'XXX_______' +
	//         'XXX_______' +
	//         'XXX_______'
	//     ),
	// });

	pages.push({
		field: Field.create(InputField), //takes in a field, example above
	});

	console.log(encoder.encode(pages));
}

#include <iostream>
#include <string>
#include <vector>
#include "Base64.h"

using namespace std;

int main() {


	Base64 b;

	b.init("8876245833 + 9101581922 + 8811935123 + 9101002649 + 8638462638");

	Base64 bb;
	
	bb.init(b.getByteArray());


	cout << b.encodeAsString() << endl;
	cout << bb.encodeAsString() << endl;

	Base64 a;

	a.init(bb.encodeAsBytes());


	cout << a.decodeAsString() << endl;

	b.init(a.decodeAsString().c_str());

	cout << b.encodeAsString() << endl;

	bb.init(b.encodeAsBytes());

	cout << bb.decodeAsString() << endl;

	cout << (a.isValid(bb.getValue())?"true":"false") << endl;

	return 0;
}
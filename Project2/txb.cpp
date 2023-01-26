#include <iostream>
#include <fstream>
#include "String.hpp"
#include <vector>

int main() {

	std::fstream in("C:\\Users\\marha\\Downloads\\misc\\txb\\input.txt");
	if (!in.is_open()) {
		std::cout << "broke lol" << std::endl;
	}

	std::ofstream out("C:\\Users\\marha\\Downloads\\misc\\txb\\output.txt", std::ios_base::app);

	String output;
	
	String beg("<span class=\"html-attribute-name\">onfocus</span>='<span class=\"html-attribute-value\">speakText(\"");
	String end("Press tab to continue.");
	String headerBeg("<span class=\"html-tag\">&lt;h2&gt;</span>");
	String headerEnd("<span class=\"html-tag\">&lt;/h2&gt;</span>");

	char temp[20001];
	while (!in.eof()) {
		String text;
		in.getline(temp, 20000);
		text = temp;
		std::cout << text.findstr(0, beg) << " ";
		if (text.findstr(0, headerBeg) != -1) {
			output = text.substr((text.findstr(0, headerBeg) + 40), (text.findstr((text.findstr(0, headerBeg)), headerEnd) - 1));
			out << output << std::endl;
		}
		if (text.findstr(0, beg) && text.findstr((text.findstr(0, beg)), end) != -1) {
			output = text.substr((text.findstr(0, beg) + 96), (text.findstr((text.findstr(0,beg)), end)-2));
			out << output << std::endl << std::endl;
		}	
	}


	in.close();
	out.close();
	

	return 0;
}
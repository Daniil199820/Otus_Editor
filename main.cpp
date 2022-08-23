#include "lib_editor.h"

int main()
{ 
	std::unique_ptr<Redactor_Model> model = std::make_unique<Redactor_Model>();
	std::unique_ptr<Redactor_View> view = std::make_unique<Redactor_View>();
	Redactor_controller r_c(std::move(model),std::move(view));
	std::cout << "Program starts" << std::endl;

	r_c.create_doc();
	r_c.export_doc();
    r_c.import_doc();
	std::cout << "Program shows form" << std::endl;
	r_c.create_line(0,100,0,50);
	std::cout << "Program shows form" << std::endl;
	r_c.create_square(40, 90, 80, 120);
	std::cout << "Program shows form" << std::endl;
	r_c.delete_object(1);
	return 0;
}
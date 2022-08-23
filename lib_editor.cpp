#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <memory>
#include <utility>
#include "lib_editor.h"

	void Graphical_object::get_coordinats() {}
	std::string Graphical_object::get_name() { return "None"; }
	void Graphical_object:: set_index(int count)
	{
		index = count;
	}
	int Graphical_object:: get_index() const
	{
		return index;
	}


	Line::Line(int x1, int x2, int y1, int y2) :x1(x1), x2(x2), y1(y1), y2(y2) {}

	std::string Line::get_name() 
	{
		return "Line";
	}

	void Line:: get_coordinats()
	{
		std::string temp = get_name() + ": " + "x1 = " + std::to_string(x1) + "; x2 = " + std::to_string(x2) + "; y1 = " + std::to_string(y1) + "; y2 = " + std::to_string(y2);
		std::cout << temp << std::endl;
	}


	Square::Square(int x, int y, int width, int height) :x(x), y(y), width(width), height(height) {}

	std::string Square::get_name()
	{
		return "Square";
	}

	void Square::get_coordinats() 
	{
		std::string temp = get_name() + ": " +"x = " + std::to_string(x) + "; y = " + std::to_string(y) + "; width = " + std::to_string(width) + "; height = " + std::to_string(height);
		std::cout << temp<<std::endl;
	}


	void Document:: set_name(std::string name_)
	{
		name = std::move(name_);
	}

	void Document:: download_from_file(std::string name_)
	{
		set_name(name_);
		//std::cout << "Document is downloaded from file - " << name<<std::endl;
	}

	void Document:: upload_to_file(std::string name_)
	{
		set_name(name_);
		//std::cout << "Document is uploaded to file - " << name<<std::endl;
	}
	
	void Document:: add_graphical_obj(std::shared_ptr<Graphical_object> object)
	{
		pool_graph_objects.emplace_back(object);
	}




	BaseFormDocument::BaseFormDocument()
	{
		std::cout << "Base form  in window!" << std::endl;
	}


	SuperFormDocument::SuperFormDocument()
	{
		std::cout << "Super form in window!" << std::endl;
	}






	std::unique_ptr<IFormDocument>UIFormBase:: make_doc_form()
	{
		return std::make_unique<BaseFormDocument>();
	}

	void UIFormBase::show_form(const std::unique_ptr<Document>& doc) const 
	{
		for (const auto& it : doc->pool_graph_objects)
		{
			it->get_coordinats();
		}
	}


	std::unique_ptr<IFormDocument> UIFormSuper:: make_doc_form()
	{
		return std::make_unique<SuperFormDocument>();
	}

	void UIFormSuper:: show_form(const std::unique_ptr<Document>& doc) const 
	{
		for (const auto& it : doc->pool_graph_objects)
		{
			it->get_coordinats();
		}
	}


	void Redactor_Model::Create_Document()
	{
		if(doc_==nullptr)
		doc_ = std::make_unique<Document>();
	}

	void Redactor_Model::Import_Document(std::string name_document)
	{
		Create_Document();
		doc_->download_from_file(name_document);
	}

	void Redactor_Model:: Export_Document(std::string name_document)
	{
		doc_->upload_to_file(name_document);
	}

	void Redactor_Model::add_Square(int x,int y,int width,int height)
	{
		if (doc_ != nullptr) 
		doc_->add_graphical_obj(std::make_shared<Square>(x, y, width, height));
	}

	void Redactor_Model::add_Line(int x1, int x2, int y1, int y2)
	{
		if (doc_ != nullptr) 
		doc_->add_graphical_obj(std::make_shared<Line>(x1, x2, y1, y2));
	}

	void Redactor_Model::remove_graphical_object(int i)
	{
		if (doc_ != nullptr)
		{
			doc_->pool_graph_objects.erase(doc_->pool_graph_objects.begin() + i);
		}
	}

    const  std::unique_ptr<Document>& Redactor_Model::get_document() const
	{
		return doc_;
	}



	void Redactor_View::create_view_doc_()
	{
		form->make_doc_form();
	}

	void Redactor_View::create_message_view(std::string window_msg)
	{
		std::cout << window_msg<<std::endl;
	}

	void Redactor_View::update_form(Redactor_Model* model)
	{
		form->show_form(model->get_document());
	}




	Redactor_controller::Redactor_controller(std::unique_ptr<Redactor_Model> _model, std::unique_ptr<Redactor_View> _view)
	{
		model = std::move(_model);
		view = std::move(_view);
	}

	void Redactor_controller::create_doc()
	{
		model->Create_Document();
		view->create_view_doc_();
	}

	void Redactor_controller::import_doc()
	{
		model->Import_Document("File import.png");
		view->create_message_view("File document import");
	}

	void Redactor_controller::export_doc()
	{
		model->Export_Document("File export.png");
		view->create_message_view("File document export");
	}

	void Redactor_controller::create_square(int x,int y,int width,int height)
	{
	    model->add_Square(x, y, width, height);
		view->update_form(model.get());
		
	}

	void Redactor_controller::create_line(int x1, int x2, int y1, int y2)
	{
		model->add_Line(x1, x2, y1, y2);
		view->update_form(model.get());
	}

	void Redactor_controller::delete_object(int i)
	{
		model->remove_graphical_object(i);
		view->update_form(model.get());
	}
	

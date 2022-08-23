#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <memory>
#include <utility>

class Graphical_object {
private:
	int index;
public:
	virtual void get_coordinats();
	virtual std::string get_name();
	void set_index(int count);
	int get_index() const;
};



class Line :public Graphical_object {
private:
	int x1, x2, y1, y2;
public:

	Line(int x1, int x2, int y1, int y2);

	std::string get_name() override;

	void get_coordinats() override;
};

class Square:public Graphical_object {
private:
	int x, y, width, height;
public:
	
	Square(int x, int y, int width, int height);

	std::string get_name() override;

	void get_coordinats() override;

};


class Document {
public:

	std::string name = "None";
	std::vector<std::shared_ptr<Graphical_object>> pool_graph_objects;
    
	Document()
	{
		//std::cout << "Document is created with name - "<<name<<std::endl;
	}

	void set_name(std::string name_);

	void download_from_file(std::string name_);

	void upload_to_file(std::string name_);
	
	void add_graphical_obj(std::shared_ptr<Graphical_object> object);
};

class IFormDocument
{
};

class BaseFormDocument :public IFormDocument
{
public:
	BaseFormDocument();
};

class SuperFormDocument :public IFormDocument
{
public:
	SuperFormDocument();
};

class IUIForm
{
public:
	virtual std::unique_ptr<IFormDocument> make_doc_form() = 0;
	virtual void show_form(const std::unique_ptr<Document>& doc) const = 0;

};

class UIFormBase:public IUIForm 
{
public:
	std::unique_ptr<IFormDocument> make_doc_form() override;

	void show_form(const std::unique_ptr<Document>& doc) const override;

};

class UIFormSuper :public IUIForm
{
public:
	std::unique_ptr<IFormDocument> make_doc_form() override;

	void show_form(const std::unique_ptr<Document>& doc) const override;
};

class Redactor_Model {
private:
	std::unique_ptr<Document> doc_ = nullptr;
public:
	void Create_Document();

	void Import_Document(std::string name_document);

	void Export_Document(std::string name_document);

	void add_Square(int x,int y,int width,int height);

	void add_Line(int x1, int x2, int y1, int y2);

	void remove_graphical_object(int i);

    const  std::unique_ptr<Document>& get_document() const;

};

class Redactor_View
{
public:
	void create_view_doc_();

	void create_message_view(std::string window_msg);

	void update_form(Redactor_Model* model);

private:
	std::unique_ptr<IUIForm> form = std::make_unique<UIFormBase>();
};

class Redactor_controller
{
private:
	std::unique_ptr<Redactor_Model> model;
	std::unique_ptr<Redactor_View> view;
public:
	//Redactor_controller() = default;
	Redactor_controller(std::unique_ptr<Redactor_Model> _model, std::unique_ptr<Redactor_View> _view);

	void create_doc();

	void import_doc();

	void export_doc();

	void create_square(int x,int y,int width,int height);

	void create_line(int x1, int x2, int y1, int y2);

	void delete_object(int i);
	
};

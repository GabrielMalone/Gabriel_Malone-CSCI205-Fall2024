#include <string>
#include <iostream>

class Contact {
public:
	// Constructor
	Contact() : name_(""), email_(""), phone_("") {}
	Contact(std::string name, std::string email, std::string phone)
		: name_(name), email_(email), phone_(phone) {}

	// Getters
	std::string getName() const { return name_; }
	std::string getEmail() const { return email_; }
	std::string getPhone() const { return phone_; }

	// Setters
	void setName(std::string name) { name_ = name; }
	void setEmail(std::string email) { email_ = email; }
	void setPhone(std::string phone) { phone_ = phone; }

	// Overload << operator
	friend std::ostream& operator<<(std::ostream& os, const Contact& contact) {
		os << "Name: " << contact.name_ << " Email: " << contact.email_ << " Phone: " << contact.phone_;
		return os;
	}

private:
	std::string name_;
	std::string email_;
	std::string phone_;
};

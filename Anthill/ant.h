#pragma once
#include <string>

class Role
{
protected:
	std::string current_role;
public:
	Role(std::string current_role_);
	virtual ~Role() = default;

	virtual void work()const = 0;
	virtual std::string getRoleName()const;
};

class Norole :public Role
{
public:
	Norole();

	void work()const override;
};

class Nanny : public Role
{
public:
    Nanny();

    void work() const override;
};

class Soldier : public Role
{
public:
    Soldier();

    void work() const override;
};

class Pastuh : public Role
{
public:
    Pastuh();

    void work() const override;
};

class Builder : public Role
{
public:
    Builder();

    void work() const override;
};

class Cleaner : public Role
{
public:
    Cleaner();

    void work() const override;
};

class Ant
{
private:
    int age;
    Role* role;
    int health;
    //bool bag true если заполнена, false если нет
public:
    Ant();
    ~Ant();

    void change_role();
    void change_age();
    void change_health(int current_health_);
    void work() const;
    void print() const;

    std::string getRoleName() const;
    int getHealth() const;
    void setHealth(int h_);
};
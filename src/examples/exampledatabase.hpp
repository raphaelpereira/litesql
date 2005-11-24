#include "litesql.hpp"
namespace example {
class Person;
class PersonPersonRelationMother {
public:
    class Row {
    public:
        litesql::Field<int> person2;
        litesql::Field<int> person1;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType person1_;
    static const litesql::FieldType person2_;
    static void link(const litesql::Database& db, const Person& o0, const Person& o1);
    static void unlink(const litesql::Database& db, const Person& o0, const Person& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<PersonPersonRelationMother::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<Person> getPerson1(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
    static litesql::DataSource<Person> getPerson2(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
};
class PersonPersonRelationFather {
public:
    class Row {
    public:
        litesql::Field<int> person2;
        litesql::Field<int> person1;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType person1_;
    static const litesql::FieldType person2_;
    static void link(const litesql::Database& db, const Person& o0, const Person& o1);
    static void unlink(const litesql::Database& db, const Person& o0, const Person& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<PersonPersonRelationFather::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<Person> getPerson1(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
    static litesql::DataSource<Person> getPerson2(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
};
class PersonPersonRelationSiblings {
public:
    class Row {
    public:
        litesql::Field<int> person2;
        litesql::Field<int> person1;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType person1_;
    static const litesql::FieldType person2_;
    static void link(const litesql::Database& db, const Person& o0, const Person& o1);
    static void unlink(const litesql::Database& db, const Person& o0, const Person& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<PersonPersonRelationSiblings::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<Person> getPerson1(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
    static litesql::DataSource<Person> getPerson2(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
};
class PersonPersonRelationChildren {
public:
    class Row {
    public:
        litesql::Field<int> person2;
        litesql::Field<int> person1;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType person1_;
    static const litesql::FieldType person2_;
    static void link(const litesql::Database& db, const Person& o0, const Person& o1);
    static void unlink(const litesql::Database& db, const Person& o0, const Person& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<PersonPersonRelationChildren::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<Person> getPerson1(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
    static litesql::DataSource<Person> getPerson2(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
};
class Person : public litesql::Persistent {
public:
    class SexType : public litesql::FieldType {
    public:
        static const int Male;
        static const int Female;
        SexType(const std::string& n, const std::string& t, const std::string& tbl, const litesql::FieldType::Values& vals=Values());
    };
    class Sex {
    public:
        static const int Male;
        static const int Female;
    };
    class MotherHandle : public litesql::RelationHandle<Person> {
    public:
        MotherHandle(const Person& owner);
        void link(const Person& o0);
        void unlink(const Person& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<Person> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<PersonPersonRelationMother::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    class FatherHandle : public litesql::RelationHandle<Person> {
    public:
        FatherHandle(const Person& owner);
        void link(const Person& o0);
        void unlink(const Person& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<Person> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<PersonPersonRelationFather::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    class SiblingsHandle : public litesql::RelationHandle<Person> {
    public:
        SiblingsHandle(const Person& owner);
        void link(const Person& o0);
        void unlink(const Person& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<Person> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<PersonPersonRelationSiblings::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    class ChildrenHandle : public litesql::RelationHandle<Person> {
    public:
        ChildrenHandle(const Person& owner);
        void link(const Person& o0);
        void unlink(const Person& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<Person> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<PersonPersonRelationChildren::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType Name;
    litesql::Field<std::string> name;
    static const litesql::FieldType Age;
    litesql::Field<int> age;
protected:
    static std::vector < std::pair< std::string, std::string > > sex_values;
public:
    static Person::SexType Sex;
    litesql::Field<int> sex;
    static void initValues();
protected:
    void defaults();
public:
    Person(const litesql::Database& db);
    Person(const litesql::Database& db, const litesql::Record& rec);
    Person(const Person& obj);
    const Person& operator=(const Person& obj);
    Person::MotherHandle mother();
    Person::FatherHandle father();
    Person::SiblingsHandle siblings();
    Person::ChildrenHandle children();
    virtual void sayHello();
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect();
    std::auto_ptr<Person> upcast();
    std::auto_ptr<Person> upcastCopy();
};
std::ostream & operator<<(std::ostream& os, Person o);
class ExampleDatabase : public litesql::Database {
public:
    ExampleDatabase(std::string backendType, std::string connInfo);
protected:
    virtual std::vector<litesql::Database::SchemaItem> getSchema() const;
    static void initialize();
};
}
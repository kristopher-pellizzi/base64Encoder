#include <string>

using std::string;

class Argument{
	private:
		char* _val;
		bool _hasVal;
		bool _isValid;

		Argument();

	protected:
		string _name;

	public:
		Argument(string name, char* val);
		Argument(string name);

		const string& getName() const;

		char* getVal() const;

		bool hasVal() const;

		bool isValid() const;

		static const Argument& getInvalidArg();


		struct ArgumentCmp{
			bool operator()(const Argument& lhs, const Argument& rhs) const;
		};
};
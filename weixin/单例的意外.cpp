#include <iostream>
#include <memory>
#include <mysql/jdbc.h>
#include <vector>
using namespace std;
using namespace sql;

class Pool;
typedef Pool* SA;

class ConnEntity{
	public:
		ConnEntity() {
			m_conn = NULL;
			Driver* driver;
			try {
				driver = get_driver_instance();
				sql::Connection* conn = driver->connect("tcp://127.0.0.1","root","wscyx970805");
				m_conn.reset(conn);
			}catch(sql::SQLException e) {
				cout << "could not connect to server. error msg:" << e.what() << endl;
				exit(1);
			}
		}
		~ConnEntity() {
			cout << "ConnEntity deconstruct." << endl;
		}

	private:
		shared_ptr<Connection> m_conn;
};

class Pool{
	private:
		Pool(){
			Init();
		}

	public:
		static SA GetInstance() {
			if (m_instance == NULL) {
				m_instance = new Pool();
			}
			return m_instance;
		}
		~Pool() {
			cout << "Pool deconstruct." << endl;
		}

	protected:
		void Init() {
			for (int i = 0; i <  5; ++i) {
				unique_ptr<ConnEntity> tmp(new ConnEntity());
				m_arr.push_back(move(tmp));
			}
		}

	private:
		static SA m_instance;
		vector<unique_ptr<ConnEntity>> m_arr;
};

class Adapta{
	public:
		static shared_ptr<Pool> GetInstance() {
			return shared_ptr<Pool>(Pool::GetInstance());
		}
};

SA Pool::m_instance = NULL;
/*shared_ptr<Pool> test(SA p) {
	shared_ptr<Pool> tmp;
	tmp.reset(p);
	return tmp;
}*/

int main(int argc,char* argv[])
{
	shared_ptr<Pool> p = Adapta::GetInstance();
	return 0;
}

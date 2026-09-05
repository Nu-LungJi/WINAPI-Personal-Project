#pragma once
namespace SAFE_DELETE_NAMESPACE {
	template<typename T>
	void SAFE_DELETE(T& P) {
		if (P) {
			delete P;
			P = nullptr;
		}
	}

	template <typename T>
	void SAFE_DELETE_VEC(vector<T>& _vec) {
		for_each(_vec.begin(), _vec.end(), SAFE_DELETE<T>);
		_vec.clear();
	}

	template <typename T>
	void SAFE_DELETE_LIST(list<T>& _list) {
		for_each(_list.begin(), _list.end(), SAFE_DELETE<T>);
		_list.clear();
	}

	template <typename T1, typename T2>
	void SAFE_DELETE_MAP(map<T1, T2>& _map) {
		typename map<T1, T2>::iterator iter = _map.begin();
		for (; iter != _map.end();) {
			if (nullptr != iter->second) { SAFE_DELETE<T2>(iter->second); }
			else { iter++; }
		}
		_map.clear();
	}
}

struct KeyFinder {
	
	const TCHAR* KeyValue;
	KeyFinder(const TCHAR* _KeyValue) : KeyValue(_KeyValue) {}

	template <typename T>
	BOOL operator()(T& _Pair) { return !lstrcmp(_Pair.first, KeyValue); }
};


//template <typename T>					
//class StateMachine {
//private:								
//		T	CurrentState;				
//public:									
//	void FSM_StateChange(T _State) 	
//		{ CurrentState = _State; }			
//	void FSM_StateEnter();
//	void FSM_StateUpdate();
//	void FSM_StateExit();
//
//
//};

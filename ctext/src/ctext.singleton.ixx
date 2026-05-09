module;

export module ctext.singleton;


export namespace ctext {
	template<typename T>
		class __declspec(novtable) Singleton {
		public:
			static T& Get() {
				static T instance;

				return instance;
			}
	};
}
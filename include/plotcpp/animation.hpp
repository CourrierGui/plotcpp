#pragma once

#include <plotcpp/figure.hpp>

namespace pcpp {

	class animation {
		public:
			using Action = std::function<bool(int,Figure&)>;
			using ActionList
				= std::vector<std::pair<Action,int>>;

		private:
			Figure     _figure;
			ActionList _actions;

		public:
			Animation(int,char**,std::size_t,std::size_t);

			auto  start() -> int;
			void init(const std::function<void(Figure&)>&);
			void add (int msec, const Action&);
	};


} /* end of namespace pcpp */

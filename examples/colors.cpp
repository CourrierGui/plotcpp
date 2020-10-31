#include <figure.hpp>

int main(int argc, char* argv[]) {
	int nb_colors = 15;

	if (argc == 2) {
		nb_colors = std::atoi(argv[1]);
	}

	pcpp::Figure f{argc, argv, 1, 1};

	for (int i=0; i<=nb_colors; ++i) {
		f.hist({static_cast<double>(i)}, {1})
			.width(1)
			.pen(0, 0, 0);
	}
	f.range(-1, nb_colors+1, 0, 1.1);

	return f.show();
}

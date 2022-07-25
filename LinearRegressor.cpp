#include "LR.h"
FILE* stream;

class Regression {
	std::vector<float> x;
	std::vector<float> y;

	float coeff; // slope
	float constTerm; //constant term for best fitting line
	float sum_xy;
	float sum_x;
	float sum_y;
	float sum_x_square;
	float sum_y_square;

public:
	Regression() { // constructor: Regression() to provide the default values
		coeff = 0;
		constTerm = 0;
		sum_y = 0;
		sum_y_square = 0;
		sum_x_square = 0;
		sum_x = 0;
		sum_xy = 0;
	}

	// function that calculates the slope of best fitting line
	void calculateCoeff() {
		unsigned __int64 n = x.size();
		float numerator = (n * sum_xy - sum_x * sum_y);
		float denominator = (n * sum_x_square - sum_x * sum_x);
		coeff = numerator / denominator;
	}

	// function to find the value of constantTerm()
	void constantTermValue() {
		unsigned __int64 n = x.size();
		float numerator = (sum_y * sum_x_square - sum_x * sum_xy);
		float denominator = (n * sum_x_square - sum_x * sum_x);
		constTerm = numerator / denominator;
	}

	size_t sizeOfData() {
		return x.size();
	}

	float constant() {
		if (constTerm == 0)
			constantTermValue();
		return constTerm;
	}

	void PrintBestFittingLine() {
		if (coeff == 0 && constTerm == 0) {
			calculateCoeff();
			constantTermValue();
		}

		std::cout << "the best fitting line is y = "
			<< coeff << "x + " << constantTermValue << std::endl;
	}

	void takeInput(int n) {
		for (int i = 0; i < n; i++) {
			char comma;
			float xi;
			float yi;
			std::cin >> xi >> yi;

			sum_xy += xi * yi; // sum of the product
			sum_x += xi;
			sum_y += yi;
			sum_x_square += xi * xi;
			sum_y_square += yi * yi;
			x.push_back(xi);
			y.push_back(yi);
		}
	}

	void showData() {
		for (int i = 0; i < 62; i++) {
			std::cout << "_";
		}

		std::cout << "\n\n";
		printf("|%15s%15s %15s%15s%20s\n", "X", "", "Y", "", "|");

		for (int i = 0; i < x.size(); i++) {
			printf("|%20f %20f%20s\n",
				x[i], y[i], "|");
		}

		for (int i = 0; i < 62; i++) {
			printf("_");
		}

		printf("\n");
	}

	float predict(float x) {
		return coeff * x + constTerm;
	}

	float errorSquare() {
		float ans = 0;
		for (int i = 0;
			i < x.size(); i++) {
			ans += ((predict(x[i]) - y[i])
				* (predict(x[i]) - y[i]));
		}
		return ans;
	}

	float errorIn(float num)
	{
		for (int i = 0;
			i < x.size(); i++) {
			if (num == x[i]) {
				return (y[i] - predict(x[i]));
			}
		}
		return 0;
	}
};

int main() {
	freopen_s(&stream, "data.txt", "r", stdin);
	Regression reg;

	int n;
	std::cin >> n;
	reg.takeInput(n);

	reg.PrintBestFittingLine();

	std::cout << "Predicted value at 2060 = " << reg.predict(2060) << std::endl;
	std::cout << "The error squared = " << reg.errorSquare() << std::endl;
	std::cout << "error in 2050 = " << reg.errorIn(2050) << std::endl;
}
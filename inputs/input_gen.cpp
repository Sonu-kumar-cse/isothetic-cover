#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    const int rows = 60;
    const int cols = 150;

    // Initialize the matrix with ones
    vector<vector<int> > matrix(rows, vector<int>(cols, 1)); // Add a space in `>>`

    // Define the center and scale of the heart shape
    double centerX = cols / 2.0;
    double centerY = rows / 2.5; // Adjusted for aspect ratio
    double scale = 15.0;         // Scale for the heart size

    // Generate the heart shape using the parametric equation
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Transform matrix coordinates into normalized heart-space coordinates
            double x = (j - centerX) / scale;
            double y = (centerY - i) / scale;

            // Heart equation: (x^2 + y^2 - 1)^3 - x^2 * y^3 <= 0
            if (pow(x * x + y * y - 1, 3) - x * x * pow(y, 3) <= 0) {
                matrix[i][j] = 0;
            }
        }
    }

    // Print the matrix
    for (size_t i = 0; i < matrix.size(); ++i) { // Use classic loops
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            cout << (matrix[i][j] == 1 ? "1 " : "0 ");
        }
        cout << endl;
    }

    return 0;
}

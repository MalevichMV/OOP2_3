#pragma once
#include <iostream>

namespace OOP
{
	class vector;
	class matrix
	{
	protected:
		static unsigned IDS;
		int mtr_id;
		double* mtr;
		unsigned int rows, cols;
		class matrixRow
		{
		public:
			matrixRow(const matrix* other, unsigned R);
			double& operator[](unsigned int ind);
			double const operator[](unsigned int ind) const;

		private:
			unsigned int r, c, R;
			double* mtr;
		};
	public:
		matrix(unsigned int r, unsigned int c, double(*genMtr)(unsigned int i, unsigned int j));
		matrix(unsigned int s = 0);
		matrix(unsigned int r, unsigned int c);
		virtual ~matrix();
		matrix(const matrix& other);
		matrix(matrix&& other);
		int CheckForSum(const matrix& other) const;
		int CheckForMult(const matrix& other) const;
		double MtrMax() const;
		double MtrMin() const;
		bool isNULL() const;
		matrixRow operator[](int ind);
		const matrixRow operator[](int ind) const;
		friend std::ostream& operator<< (std::ostream& out, const matrix& other);
		matrix& operator=(const matrix& other);
		matrix& operator=(matrix&& other);
		matrix& operator+=(const matrix& other);
		matrix& operator-=(const matrix& other);
		matrix& operator*=(const double k);
		matrix& operator*=(const matrix& other);
		friend matrix operator+(const matrix& a, const matrix& b);
		friend matrix operator-(const matrix& a, const matrix& b);
		friend matrix operator*(const matrix& a, const matrix& b);
		friend matrix operator*(const matrix& a, double k);

		unsigned int Get_cols() const;
		unsigned int Get_rows() const;
	};

	class vector : public matrix
	{
	public:
		vector(unsigned int r = 3);
		vector(unsigned int r, double(*genVec)(unsigned int i));
		~vector() override;
		vector(const matrix& other);
		vector(matrix&& other);
		vector& operator=(const matrix& other);
		vector& operator=(matrix&& other);
		vector& operator+=(const matrix& other);
		vector& operator-=(const matrix& other);
		vector& operator*=(const double k);
		vector& operator*=(const matrix& other);

		double& operator[](unsigned int ind);
		double const operator[](unsigned int ind) const;
	};

	void fill(int r, int c, double* mtr);
}

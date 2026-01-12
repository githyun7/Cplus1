#include <iostream>
#include <cmath> // for std::round

int main() 
{
    // Declare maximum and achieved grades
    double F_max, F_ur;
    double M_max, M_ur;
    double P1_max, P1_ur;
    double P2_max, P2_ur;
    double P3_max, P3_ur;
    double P4_max, P4_ur;
    double P5_max, P5_ur;

    // Input final exam with validation
    do 
    {
        std::cout << "Enter the maximum grade on the final examination: ";
        std::cin >> F_max;
    } while (F_max <= 0 || F_max != std::round(F_max));

    do 
    {
        std::cout << "Enter your grade on the final examination: ";
        std::cin >> F_ur;
    } while (F_ur < 0 || F_ur > F_max);

    // Input mid-term exam with validation
    do 
    {
        std::cout << "Enter the maximum grade on the mid-term examination: ";
        std::cin >> M_max;
    } while (M_max <= 0 || M_max != std::round(M_max));

    do 
    {
        std::cout << "Enter your grade on the mid-term examination: ";
        std::cin >> M_ur;
    } while (M_ur < 0 || M_ur > M_max);

    // Input projects with validation
    do 
    {
        std::cout << "Enter the maximum grade on project 1: ";
        std::cin >> P1_max;
    } while (P1_max <= 0 || P1_max != std::round(P1_max));

    do 
    {
        std::cout << "Enter your grade on project 1: ";
        std::cin >> P1_ur;
    } while (P1_ur < 0 || P1_ur > P1_max);

    do 
    {
        std::cout << "Enter the maximum grade on project 2: ";
        std::cin >> P2_max;
    } while (P2_max <= 0 || P2_max != std::round(P2_max));

    do 
    {
        std::cout << "Enter your grade on project 2: ";
        std::cin >> P2_ur;
    } while (P2_ur < 0 || P2_ur > P2_max);

    do 
    {
        std::cout << "Enter the maximum grade on project 3: ";
        std::cin >> P3_max;
    } while (P3_max <= 0 || P3_max != std::round(P3_max));

    do 
    {
        std::cout << "Enter your grade on project 3: ";
        std::cin >> P3_ur;
    } while (P3_ur < 0 || P3_ur > P3_max);

    do 
    {
        std::cout << "Enter the maximum grade on project 4: ";
        std::cin >> P4_max;
    } while (P4_max <= 0 || P4_max != std::round(P4_max));

    do 
    {
        std::cout << "Enter your grade on project 4: ";
        std::cin >> P4_ur;
    } while (P4_ur < 0 || P4_ur > P4_max);

    do 
    {
        std::cout << "Enter the maximum grade on project 5: ";
        std::cin >> P5_max;
    } while (P5_max <= 0 || P5_max != std::round(P5_max));

    do 
    {
        std::cout << "Enter your grade on project 5: ";
        std::cin >> P5_ur;
    } while (P5_ur < 0 || P5_ur > P5_max);

    // Calculate percentage scores
    double F_100 = 100.0 * F_ur / F_max;
    double M_100 = 100.0 * M_ur / M_max;
    double P1_100 = 100.0 * P1_ur / P1_max;
    double P2_100 = 100.0 * P2_ur / P2_max;
    double P3_100 = 100.0 * P3_ur / P3_max;
    double P4_100 = 100.0 * P4_ur / P4_max;
    double P5_100 = 100.0 * P5_ur / P5_max;

    // Ensure all grades are at least the final exam score
    if (M_100 < F_100) M_100 = F_100;
    if (P1_100 < F_100) P1_100 = F_100;
    if (P2_100 < F_100) P2_100 = F_100;
    if (P3_100 < F_100) P3_100 = F_100;
    if (P4_100 < F_100) P4_100 = F_100;
    if (P5_100 < F_100) P5_100 = F_100;

    // Calculate weighted exam average
    double E_100 = (3.0 / 4.0) * F_100 + (1.0 / 4.0) * M_100;

    // Calculate average project score
    double P_100 = (P1_100 + P2_100 + P3_100 + P4_100 + P5_100) / 5.0;

    double weight, final_grade;

    // Determine final grade based on exam average
    if (E_100 <= 40.0) 
    {
        final_grade = E_100;
    } 
    else if (E_100 >= 60.0) 
    {
        final_grade = (2.0 / 3.0) * E_100 + (1.0 / 3.0) * P_100;
    } 
    else 
    {
        weight = (E_100 - 40.0) / 20.0;
        final_grade = P_100 * (1.0 / 3.0) * weight + E_100 * (1.0 - (1.0 / 3.0) * weight);
    }

    // Round the final grade to the nearest integer, breaking ties upward
    final_grade = std::round(final_grade + 1e-12);

    std::cout << "Final grade: " << (int)(final_grade) << std::endl;

    return 0;
}
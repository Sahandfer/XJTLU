# Assignment 2 - Exercise 1
## Problem Statement
The first problem (Exercise 1) asks us to design an iFraction class, which is derived as a sub-class to the already created Fraction. Essentially, all the characteristics that were defined for the fraction class should also be available for the iFraction class. Therefore, the mentioned characteristics would be overwritten in order for them to be usable by the iFraction objects. It is also mentioned that these mixed fractions (iFractions) are defined by the user and therefore, we must get an input from the user and consequently, design our program in a way that would be able to create an iFraction object from the given input.

## Analysis
The input for this program would be an integer called choice which allows the user to travel around the user interface and use all the functionalities provided in the menu. Additionally, there is an integer called whichType, which would allow the user to choose between entering improper and mixed fractions. Moreover, there are integers for determining the decimal part, numerator and denominator of the mixed fraction as well as a string for when the user wants to convert a decimal to a fraction.
The output for this program can either be an iFraction, Fraction, or decimal depending on what options the user chooses to use.
There are several variables required in order to insure the functionality of this program. The main ones are the three regarding the decimal part, numerator and denominator of the mixed fraction. The variables that were mentioned in creating the Fraction class, such as greatest common integer, choice, etc., are also implemented here likewise.
Design
As the first step of the algorithm, a menu is designed to provide the user different options to use within the program. This menu consists of 9 different options that the user can choose from. Since this is a sub-class of the Fraction class, a lot of the functions that are used here work the same as the functions used for Fraction class and are only overloaded in order to be applicable to iFraction class objects.
In addition to the three main functions that were used in almost all of the parts of algorithm when designing the Fraction class (gcd finder, showFraction, normalise), the two functions convertF and convertIF were also created in order to convert Fraction objects to iFraction objects vice versa respectively.
convertF function:
Here, first we receive a Fraction object as an input to the function. Then we normalise this Fraction in order to ensure that it is in its simplest form. Next, based on the sign and magnitude of the numerator and denominator of the given fraction, we have a set of if conditions that would determine the equivalent mixed fraction (iFraction object).
If the absolute value of the numerator is smaller than the denominator, then the decimal part is zero and the numerator and the denominator of the mixed fraction are equal to the numerator and denominator of the improper fraction.
If the absolute value of the numerator is equal to the denominator, then the decimal part would be one and the numerator and the denominator would be zero and one respectively (To show that the fraction part of the mixed fraction is zero and we only have decimal part).
If the absolute value of the numerator is greater than the denominator, then we have three possibilities. If the numerator is negative, then the decimal part is minus the decimal part of the division of the absolute value of numerator divided by the denominator and the numerator is the remainder of this division while the denominator stays the same. If the numerator is zero, the decimal part would also be zero and the denominator would be set to one to present the simplest form. If the numerator is positive, the decimal part would be the decimal part of the numerator divided by the denominator, the numerator would be the remainder of the mentioned division while we use the same denominator for the mixed fraction.
convertIF:
First, we would receive an iFraction object as an input. Then we use a set of if conditions in order to convert this object into a Fraction object.
If the decimal part is zero, we simply have the numerator and the denominator of the mixed fraction be equal to the numerator and the denominator of the improper fraction respectively.
If the decimal part is not zero, the numerator of the improper fraction would be equal to the multiplication of the decimal part and denominator added to the numerator while the denominator stays the same for both improper and mixed fractions.
showFraction function:
This function is used to display iFraction objects. Here we get an iFraction object as an input and separate its decimal part, numerator and denominator. Now, we would print the following to display the mixed fraction: decimal part(numerator/denominator).
The explanation of the algorithm of each of the nine options, which are included in the menu, is provided below:
1) Find the sum
2) Find the difference
3) Find the multiplication
4) Find the division
5) Convert Fraction to decimal
6) Convert decimal to Fraction
7) Compare two Fractions
For the seven options mentioned above, first we convert the input iFraction object into a Fraction object using the convertIF function. Then we use the seven equivalent functions (functions with the same name) that were used for Fraction objects in order to find the desired result. Next, we would use the convertF function to convert the result, which is a Fraction object, to an iFraction object and use the showFraction function to display the results on the screen.
It should be mentioned that, every time that the user chooses one of the mentioned options a message would prompt that asks them to choose between entering an improper or a mixed function. From there, the program takes two paths depending on what the user chooses.
8) Convert improper fraction to mixed fraction
We simply use the convertF function. The algorithm of this function has been explained above.
9) Convert mixed fraction to improper fraction
We simply use the convertIF function. The algorithm of this function has been explained above.
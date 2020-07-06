package coursework3;

import static coursework3.FileHandler.deleteAll;

import java.util.ArrayList;
import java.util.Scanner;

public class CW3Main {

    public static void main(String[] args) {
        CW3Main initiater = new CW3Main(); //This is just to make things cleaner, so we call a constructor
    }

    public CW3Main() {
        menu(); //calling menu from the constructor
    }

    private void menu() {
        SkillSorter callSkillSorter = new SkillSorter(); //This is for being able to call the methods available in SkillSorter class (making an skillSorter object)
        Scanner keyboard = new Scanner(System.in);
        int loopHolder = 0; //This is for the while loop used to run the menu until the user refuses to do so 
        int Input = 0; //This is a variable to be used to point to different cases in the switch
        callSkillSorter.readVolunteersfromFile(); //here we called the readVolunteers methode from skillSorter class to restore the volunteers in the previous process

        while (loopHolder == 0) {
            String firstSkill = " "; //A string variable to hold the first letter of the skill
            String secondSkill = " "; //A string variable to hold the second letter of the skill
            String thirdSkill = " "; //A string variable to hold the third letter of the skill
            String skillSet = " "; //A string variable to hold the combination of the mentioned three letters a.k.a the skillset of the volunteer
            int loopHolder1 = 0; //This is for the while loop used to receive the first letter of the skillset as an input
            int loopHolder2 = 0;//This is for the while loop used to receive the second letter of the skillset as an input
            int loopHolder3 = 0;//This is for the while loop used to receive the third letter of the skillset as an input
            int loopHold = 0; //This is for the while loop used to receive the group from which the user wants to remove a volunteer
            int loopHoldFrom = 0; //This is for the while loop to receive which group the volunteer wants to move the volunteer from
            int loopHoldTo = 0; //This is for the while loop to receive which group the volunteer wants to move the volunteer from
            String fromGP = ""; //This is for testing that the group from is an integer, so we needed a string to be parsed into an int
            String toGP = ""; //This is for testing that the group to is an integer, so we needed a string to be parsed into an int
            int fromGroup = 0; //This is variable used to indicate which group the user wants to move the volunteer from
            int toGroup = 0; //This is variable used to indicate which group the user wants to move the volunteer to

            System.out.println("Please choose the number for one of the following options: \n1) Add a Volunteer \n2) Move a Volunteer\n3) Delete a Volunteer "
                    + "\n4) Delete all Volunteers \n5) Display groups \n6) Save and Exit");

            boolean validInput = false;
            while (validInput == false) { //This while loop is to check whether the user inputs an integer or not
                String inputChoice = keyboard.nextLine();
                try {
                    int inputChoiceNum = Integer.parseInt(inputChoice); //If we can parse the string into an integer, it is acceptable
                    Input = inputChoiceNum;
                    validInput = true;
                } catch (NumberFormatException e) {
                    System.out.println("Invalid choice! Please enter one of the given numbers only!");
                }

            }

            switch (Input) {
                case 1: //Adding a volunteer
                    //This while loop is for getting the first letter of the skill
                    while (loopHolder1 == 0) { 
                        System.out.println("Please enter the first skill of the volunteer you want to add in: ");
                        firstSkill = keyboard.nextLine();
                        try {
                            int inputchecker = Integer.parseInt(firstSkill);
                            System.out.println("Please put in only letters as skills (Only A,B,C,D,E acceptable!)");

                        } catch (NumberFormatException a) {
                            if ((firstSkill.equalsIgnoreCase("a")) || (firstSkill.equalsIgnoreCase("b")) || (firstSkill.equalsIgnoreCase("c"))
                                    || (firstSkill.equalsIgnoreCase("d")) || (firstSkill.equalsIgnoreCase("e"))) {
                                loopHolder1 = 1;

                            } else {
                                System.out.println("Only skills with letters A,B,C,D,E are acceptable! Please Try again!");
                            }

                        }
                    }
                    //This while loop is for getting the second letter of the skill
                    while (loopHolder2 == 0) {
                        System.out.println("Please enter the second skill of the volunteer you want to add in: ");
                        secondSkill = keyboard.nextLine();
                        try {
                            int inputchecker = Integer.parseInt(secondSkill);
                            System.out.println("Please put in only letters as skills (Only A,B,C,D,E acceptable!)");

                        } catch (NumberFormatException b) {
                            if ((secondSkill.equalsIgnoreCase("a")) || (secondSkill.equalsIgnoreCase("b")) || (secondSkill.equalsIgnoreCase("c"))
                                    || (secondSkill.equalsIgnoreCase("d")) || (secondSkill.equalsIgnoreCase("e"))) {
                                loopHolder2 = 1;
                            } else {

                            }
                        }
                    }
                    //This while loop is for getting the third letter of the skill
                    while (loopHolder3 == 0) {
                        System.out.println("Please enter the third skill of the volunteer you want to add in: ");
                        thirdSkill = keyboard.nextLine();
                        try {
                            int inputchecker = Integer.parseInt(thirdSkill);
                            System.out.println("Please put in only letters as skills (Only A,B,C,D,E acceptable!)");
                        } catch (NumberFormatException c) {
                            if ((thirdSkill.equalsIgnoreCase("a")) || (thirdSkill.equalsIgnoreCase("b")) || (thirdSkill.equalsIgnoreCase("c"))
                                    || (thirdSkill.equalsIgnoreCase("d")) || (thirdSkill.equalsIgnoreCase("e"))) {
                                //System.out.println(firstSkill + " " + secondSkill + " " + thirdSkill);
                                System.out.println("You have successfully entered the skills required for creating your Volunteer");
                                loopHolder3 = 1;

                            } else {
                                System.out.println("Only skills with letters A,B,C,D,E are acceptable! Please Try again!");
                            }
                        }
                    }

                    skillSet = (firstSkill + secondSkill + thirdSkill).toUpperCase();
                    System.out.println(skillSet);
                    Volunteer vol = new Volunteer(skillSet); //We make a new volunteer object from the given skillSet
                    callSkillSorter.addVolunteer(vol); //We add the volunteer object by using the add volunteer methode from skillSorter class

                    int repeatLoopHolder1 = 0; //this is to hold the loop for the following while loop
                    System.out.println("Do you want to continue? yes or no \n(Process won't be saved if you answer no)");
                    while (repeatLoopHolder1 == 0) { //This is to ask the user whether they want to continue using the program or not
                        String answer = keyboard.nextLine();
                        if (answer.equalsIgnoreCase("yes")) {
                            repeatLoopHolder1 = 1;
                        } else if (answer.equalsIgnoreCase("no")) {
                            System.out.println("The program has been terminated!");
                            repeatLoopHolder1 = 1;
                            loopHolder = 1;
                        } else {
                            System.out.println("Please only put in yes or no! Other answers are not acceptable!");
                        }
                    }
                    break;

                case 2: //Moving a Volunteer

                    ArrayList<CommunityGroup> myGroups = new ArrayList();
                    myGroups = callSkillSorter.getCommunityGroups(); //Here we get myGroups containing all the communityGroups and store it in an arraylist with similar type and name
                    callSkillSorter.displayAllVolunteers(); //To show the user the available groups and volunteers to choose from
                    System.out.println("Which Group do you want to move the volunteer from?\n1) Group 1 \n2) Group 2\n3) Group 3\n4) Group 4\n5) Group 5");
                    //A while loop to ask the user which group they want to move the volunteer from
                    while (loopHoldFrom == 0) { //This is for checking that the user inputs a number to point at a group
                        fromGP = keyboard.nextLine();
                        try {
                            fromGroup = Integer.parseInt(fromGP);
                            if ((fromGroup == 1) || (fromGroup == 2) || (fromGroup == 3) || (fromGroup == 4) || (fromGroup == 5)) {
                                loopHoldFrom = 1;
                            } else {
                                System.out.println("Please put only 1,2,3,4,5! no other numbers allowed");
                            }
                        } catch (NumberFormatException d) {
                            System.out.println("please put in a number from 1-5, no letters allowed!");
                        }
                    }
                    
                    //A while loop to ask the user the first letter of the skillSet 
                    while (loopHolder1 == 0) {
                        System.out.println("Please enter the first skill of the volunteer you want to move: ");
                        firstSkill = keyboard.nextLine();
                        try {
                            int inputchecker = Integer.parseInt(firstSkill);
                            System.out.println("Please put in only letters as skills (Only A,B,C,D,E acceptable!)");

                        } catch (NumberFormatException a) {
                            if ((firstSkill.equalsIgnoreCase("a")) || (firstSkill.equalsIgnoreCase("b")) || (firstSkill.equalsIgnoreCase("c"))
                                    || (firstSkill.equalsIgnoreCase("d")) || (firstSkill.equalsIgnoreCase("e"))) {
                                loopHolder1 = 1;

                            } else {
                                System.out.println("Only skills with letters A,B,C,D,E are acceptable! Please Try again!");
                            }

                        }
                    }
                    //A while loop to ask for the second letter of the skillset
                    while (loopHolder2 == 0) {
                        System.out.println("Please enter the second skill of the volunteer you want to move: ");
                        secondSkill = keyboard.nextLine();
                        try {
                            int inputchecker = Integer.parseInt(secondSkill);
                            System.out.println("Please put in only letters as skills (Only A,B,C,D,E acceptable!)");

                        } catch (NumberFormatException b) {
                            if ((secondSkill.equalsIgnoreCase("a")) || (secondSkill.equalsIgnoreCase("b")) || (secondSkill.equalsIgnoreCase("c"))
                                    || (secondSkill.equalsIgnoreCase("d")) || (secondSkill.equalsIgnoreCase("e"))) {
                                loopHolder2 = 1;
                            } else {

                            }
                        }
                    }
                    //A while loop to ask for the second letter of the skillset
                    while (loopHolder3 == 0) {
                        System.out.println("Please enter the third skill of the volunteer you want to move: ");
                        thirdSkill = keyboard.nextLine();
                        try {
                            int inputchecker = Integer.parseInt(thirdSkill);
                            System.out.println("Please put in only letters as skills (Only A,B,C,D,E acceptable!)");
                        } catch (NumberFormatException c) {
                            if ((thirdSkill.equalsIgnoreCase("a")) || (thirdSkill.equalsIgnoreCase("b")) || (thirdSkill.equalsIgnoreCase("c"))
                                    || (thirdSkill.equalsIgnoreCase("d")) || (thirdSkill.equalsIgnoreCase("e"))) {

                                System.out.println("You have successfully entered the skills required for moving your Volunteer");
                                loopHolder3 = 1;

                            } else {
                                System.out.println("Only skills with letters A,B,C,D,E are acceptable! Please Try again!");
                            }
                        }
                    }
                    //These series of if and else conditions sorts the skillset alphabetically
                    if (firstSkill.compareToIgnoreCase(secondSkill) > 0) {
                        if (firstSkill.compareToIgnoreCase(thirdSkill) > 0) {
                            if (secondSkill.compareToIgnoreCase(thirdSkill) > 0) {
                                skillSet = (thirdSkill + secondSkill + firstSkill).toUpperCase();
                            } else {
                                skillSet = (secondSkill + thirdSkill + firstSkill).toUpperCase();
                            }
                        } else {
                            skillSet = (secondSkill + firstSkill + thirdSkill).toUpperCase();
                        }
                    } else {
                        if (firstSkill.compareToIgnoreCase(thirdSkill) < 0) {
                            if (secondSkill.compareToIgnoreCase(thirdSkill) < 0) {
                                skillSet = (firstSkill + secondSkill + thirdSkill).toUpperCase();
                            } else {
                                skillSet = (firstSkill + thirdSkill + secondSkill).toUpperCase();
                            }
                        } else {
                            skillSet = (thirdSkill + firstSkill + secondSkill).toUpperCase();
                        }
                    }
                    
                    
                    //this is a while loop to get input for which group to move the volunteer into
                    System.out.println("Which Group do you want to move the volunteer to?\n1) Group 1 \n2) Group 2\n3) Group 3\n4) Group 4\n5) Group 5");
                    while (loopHoldTo == 0) { //This is for checking that the user inputs a number to point at a group
                        toGP = keyboard.nextLine();
                        try {
                            toGroup = Integer.parseInt(toGP);
                            if ((toGroup == 1) || (toGroup == 2) || (toGroup == 3) || (toGroup == 4) || (toGroup == 5)) {
                                loopHoldTo = 1;
                            } else {
                                System.out.println("Please put only 1,2,3,4,5! no other numbers allowed");
                            }
                        } catch (NumberFormatException d) {
                            System.out.println("please put in a number from 1-5, no letters allowed!");
                        }
                    }
                    
                    //After getting the groups to move the volunteer to and from, and the volunteer itself, we call the moveVolunteer methode
                    callSkillSorter.moveVolunteer(skillSet, myGroups.get(fromGroup - 1), myGroups.get(toGroup - 1));
                    deleteAll(); //This is to delete what was saved in the files during the last process. 
                    
                    //Another while loop to ask the user whether they want to continue or not
                    int repeatLoopHolder2 = 0; //this is to hold the loop for the following while loop
                    System.out.println("Do you want to continue? yes or no \n(Process won't be saved if you answer no)");
                    while (repeatLoopHolder2 == 0) {
                        String answer = keyboard.nextLine();
                        if (answer.equalsIgnoreCase("yes")) {
                            repeatLoopHolder2 = 1;
                        } else if (answer.equalsIgnoreCase("no")) {
                            System.out.println("The program has been terminated!");
                            repeatLoopHolder2 = 1;
                            loopHolder = 1;
                        } else {
                            System.out.println("Please only put in yes or no! Other answers are not acceptable!");
                        }
                    }

                    break;

                case 3: //Removing a volunteer
                    //We get myGroups containing all the communityGroups by calling the getCommunityGroups method from skillSorter class
                    myGroups = callSkillSorter.getCommunityGroups();
                    callSkillSorter.displayAllVolunteers();//To show the user the available groups and volunteers to choose from
                    System.out.println("Which Group do you want to remove the volunteer from? \n1) Group 1 \n2) Group 2\n3) Group 3\n4) Group 4\n5) Group 5");
                    while (loopHold == 0) { //This is for checking that the user inputs a number to point at a group
                        fromGP = keyboard.nextLine();
                        try {
                            fromGroup = Integer.parseInt(fromGP);
                            if ((fromGroup == 1) || (fromGroup == 2) || (fromGroup == 3) || (fromGroup == 4) || (fromGroup == 5)) {
                                loopHold = 1;
                            } else {
                                System.out.println("Please put only 1,2,3,4,5! no other numbers allowed");
                            }
                        } catch (NumberFormatException d) {
                            System.out.println("please put in a number from 1-5, no letters allowed!");
                        }
                    }
                    //The following three while loops are for receieving each of the three letters of the skillset
                    while (loopHolder1 == 0) {
                        System.out.println("Please enter the first skill of the volunteer you want to remove: ");
                        firstSkill = keyboard.nextLine();
                        try {
                            int inputchecker = Integer.parseInt(firstSkill);
                            System.out.println("Please put in only letters as skills (Only A,B,C,D,E acceptable!)");

                        } catch (NumberFormatException a) {
                            if ((firstSkill.equalsIgnoreCase("a")) || (firstSkill.equalsIgnoreCase("b")) || (firstSkill.equalsIgnoreCase("c"))
                                    || (firstSkill.equalsIgnoreCase("d")) || (firstSkill.equalsIgnoreCase("e"))) {
                                loopHolder1 = 1;

                            } else {
                                System.out.println("Only skills with letters A,B,C,D,E are acceptable! Please Try again!");
                            }

                        }
                    }

                    while (loopHolder2 == 0) {
                        System.out.println("Please enter the second skill of the volunteer you want to remove: ");
                        secondSkill = keyboard.nextLine();
                        try {
                            int inputchecker = Integer.parseInt(secondSkill);
                            System.out.println("Please put in only letters as skills (Only A,B,C,D,E acceptable!)");

                        } catch (NumberFormatException b) {
                            if ((secondSkill.equalsIgnoreCase("a")) || (secondSkill.equalsIgnoreCase("b")) || (secondSkill.equalsIgnoreCase("c"))
                                    || (secondSkill.equalsIgnoreCase("d")) || (secondSkill.equalsIgnoreCase("e"))) {
                                loopHolder2 = 1;
                            } else {

                            }
                        }
                    }

                    while (loopHolder3 == 0) {
                        System.out.println("Please enter the third skill of the volunteer you want to remove: ");
                        thirdSkill = keyboard.nextLine();
                        try {
                            int inputchecker = Integer.parseInt(thirdSkill);
                            System.out.println("Please put in only letters as skills (Only A,B,C,D,E acceptable!)");
                        } catch (NumberFormatException c) {
                            if ((thirdSkill.equalsIgnoreCase("a")) || (thirdSkill.equalsIgnoreCase("b")) || (thirdSkill.equalsIgnoreCase("c"))
                                    || (thirdSkill.equalsIgnoreCase("d")) || (thirdSkill.equalsIgnoreCase("e"))) {

                                System.out.println("You have successfully entered the skills required for removing your Volunteer");
                                loopHolder3 = 1;

                            } else {
                                System.out.println("Only skills with letters A,B,C,D,E are acceptable! Please Try again!");
                            }
                        }
                    }
                    //The following if conditions are to alphabetically sort the input skillset
                    if (firstSkill.compareToIgnoreCase(secondSkill) > 0) {
                        if (firstSkill.compareToIgnoreCase(thirdSkill) > 0) {
                            if (secondSkill.compareToIgnoreCase(thirdSkill) > 0) {
                                skillSet = (thirdSkill + secondSkill + firstSkill).toUpperCase();
                            } else {
                                skillSet = (secondSkill + thirdSkill + firstSkill).toUpperCase();
                            }
                        } else {
                            skillSet = (secondSkill + firstSkill + thirdSkill).toUpperCase();
                        }
                    } else {
                        if (firstSkill.compareToIgnoreCase(thirdSkill) < 0) {
                            if (secondSkill.compareToIgnoreCase(thirdSkill) < 0) {
                                skillSet = (firstSkill + secondSkill + thirdSkill).toUpperCase();
                            } else {
                                skillSet = (firstSkill + thirdSkill + secondSkill).toUpperCase();
                            }
                        } else {
                            skillSet = (thirdSkill + firstSkill + secondSkill).toUpperCase();
                        }
                    }
                    //System.out.println("you have put in: "+ skillSet);
                    //Then we call the deleteVolunteer method from the skillSorter class to remove the input volunteer from the input group
                    callSkillSorter.deleteVolunteer(skillSet, myGroups.get(fromGroup - 1));
                    deleteAll();//This is to delete what was saved in the files during the last process. 
                    
                    //Another while loop to ask the user whether they want to continue or not
                    int repeatLoopHolder3 = 0; //this is to hold the loop for the following while loop
                    System.out.println("Do you want to continue? yes or no \n(Process won't be saved if you answer no)");
                    while (repeatLoopHolder3 == 0) {
                        String answer = keyboard.nextLine();
                        if (answer.equalsIgnoreCase("yes")) {
                            repeatLoopHolder3 = 1;
                        } else if (answer.equalsIgnoreCase("no")) {
                            System.out.println("The program has been terminated!");
                            repeatLoopHolder3 = 1;
                            loopHolder = 1;
                        } else {
                            System.out.println("Please only put in yes or no! Other answers are not acceptable!");
                        }
                    }
                    break;

                case 4: //Deleting all volunteers
                    
                    callSkillSorter.deleteAllVolunteers(); //We call the deleteAllVolunteers methode from the skillSorter class
                    deleteAll(); //This is to delete what was saved in the files during the last process. 
                    //Another while loop to ask the user whether they want to continue or not
                    int repeatLoopHolder4 = 0; //this is to hold the loop for the following while loop
                    System.out.println("Do you want to continue? yes or no \n(Process won't be saved if you answer no)");
                    while (repeatLoopHolder4 == 0) {
                        String answer = keyboard.nextLine();
                        if (answer.equalsIgnoreCase("yes")) {
                            repeatLoopHolder4 = 1;
                        } else if (answer.equalsIgnoreCase("no")) {
                            System.out.println("The program has been terminated!");
                            repeatLoopHolder4 = 1;
                            loopHolder = 1;
                        } else {
                            System.out.println("Please only put in yes or no! Other answers are not acceptable!");
                        }
                    }

                    break;

                case 5: //Displaying all the groups

                    callSkillSorter.displayAllVolunteers(); //We call the displayAllVolunteers methode from the skillSorter class
                    //Another while loop to ask the user whether they want to continue or not
                    int repeatLoopHolder = 0; //this is to hold the loop for the following while loop
                    System.out.println("Do you want to continue? yes or no \n(Process won't be saved if you answer no)");
                    while (repeatLoopHolder == 0) {
                        String answer = keyboard.nextLine();
                        if (answer.equalsIgnoreCase("yes")) {
                            repeatLoopHolder = 1;
                        } else if (answer.equalsIgnoreCase("no")) {
                            System.out.println("The program has been terminated!");
                            repeatLoopHolder = 1;
                            loopHolder = 1;
                        } else {
                            System.out.println("Please only put in yes or no! Other answers are not acceptable!");
                        }
                    }
                    break;

                case 6: //Saving the program's progress into a file and exiting the program
                    deleteAll(); //This is to delete what was saved in the files during the last process. 
                    callSkillSorter.saveVolunteers(); //We call the methode from skillSorter class to save the current process of the program
                    System.out.println("The data has been saved and the program has been terminated!");
                    loopHolder = 1; //We set loopHolder to 1 so that the program end and does not loop again

                    break;

                default: //This is not one of the possible options and if the user chooses any number other than 1-6, they will be asked to re-Enter
                    System.out.println("Invalid option! Please Try again! (only input numbers 1-6)");
            }

        }

    }
}

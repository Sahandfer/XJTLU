package coursework3;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

/**
 *
 * @author sahandsabour (1614650)
 */
public class FileHandler { //This the class is created to save the process of the program and then read the data back once the program restarts

    public FileHandler() { //This is the constructor for this class

    }

    public static void storeVolunteers(ArrayList<Volunteer> Group, int groupNum) { //This is to save the data once the user chooses to do so

        ArrayList<Volunteer> Volunteers = new ArrayList<>();
        Volunteers = Group; //A temporary arraylist to store the volunteers of each group

        File volunteerList = new File("Volunteer_List.txt"); //just an unused initial value

        if (groupNum == 1) {
            volunteerList = new File("Volunteer_List_Group1.txt"); //The file for saving volunteers of group 1
        } else if (groupNum == 2) {
            volunteerList = new File("Volunteer_List_Group2.txt"); //The file for saving volunteers of group 2
        } else if (groupNum == 3) {
            volunteerList = new File("Volunteer_List_Group3.txt"); //The file for saving volunteers of group 3
        } else if (groupNum == 4) {
            volunteerList = new File("Volunteer_List_Group4.txt"); //The file for saving volunteers of group 4
        } else if (groupNum == 5) {
            volunteerList = new File("Volunteer_List_Group5.txt");//The file for saving volunteers of group 5
        }
        try {
            BufferedWriter volunteerWriter = new BufferedWriter(new FileWriter(volunteerList, true));
            for (Volunteer vol : Group) { //This will go through all volunteers in the arraylist and add their skillsets into the textfile for that group
                volunteerWriter.write(vol.getSkillSet());

                volunteerWriter.newLine();
            }

            volunteerWriter.flush();
            volunteerWriter.close();
        } catch (IOException e) {
            System.out.println("Error writing file!");
        }
    }

    public static ArrayList<Volunteer> readVolunteers(int groupNum) { //This is for reading the saved document once the program restarts
        ArrayList<Volunteer> Volunteers = new ArrayList<>();
        File volunteerList = new File("Volunteer_List.txt"); //Just an unused initial value
        if (groupNum == 1) {
            volunteerList = new File("Volunteer_List_Group1.txt"); //The file for saving volunteers of group 1
        } else if (groupNum == 2) {
            volunteerList = new File("Volunteer_List_Group2.txt"); //The file for saving volunteers of group 2
        } else if (groupNum == 3) {
            volunteerList = new File("Volunteer_List_Group3.txt"); //The file for saving volunteers of group 3
        } else if (groupNum == 4) {
            volunteerList = new File("Volunteer_List_Group4.txt"); //The file for saving volunteers of group 4
        } else if (groupNum == 5) {
            volunteerList = new File("Volunteer_List_Group5.txt"); //The file for saving volunteers of group 5
        }

        String skillSet = ""; //a variable to hold the skillset of the volunteers to be read and used to make a volunter object, then the object is added to the arraylist
        try {
            BufferedReader volunteerReader = new BufferedReader(new FileReader(volunteerList));
            while ((skillSet = volunteerReader.readLine()) != null) {
                Volunteer vol = new Volunteer(skillSet);
                Volunteers.add(vol);
            }

        } catch (IOException e) {
            System.out.println("Error reading file!");
        }
        return Volunteers;
    }

    public static void deleteAll() { //This for deleting the previous saved data once change is made (added, moved or deleted volunteers)
        File volunteerList1 = new File("Volunteer_List_Group1.txt"); //The file for saving volunteers of group 1
        File volunteerList2 = new File("Volunteer_List_Group2.txt"); //The file for saving volunteers of group 2
        File volunteerList3 = new File("Volunteer_List_Group3.txt"); //The file for saving volunteers of group 3
        File volunteerList4 = new File("Volunteer_List_Group4.txt"); //The file for saving volunteers of group 4
        File volunteerList5 = new File("Volunteer_List_Group5.txt"); //The file for saving volunteers of group 5

        try {
            BufferedWriter volunteerWriterGP1 = new BufferedWriter(new FileWriter(volunteerList1, false)); //This will delete the data in group 1 file
            BufferedWriter volunteerWriterGP2 = new BufferedWriter(new FileWriter(volunteerList2, false)); //This will delete the data in group 2 file
            BufferedWriter volunteerWriterGP3 = new BufferedWriter(new FileWriter(volunteerList3, false)); //This will delete the data in group 3 file
            BufferedWriter volunteerWriterGP4 = new BufferedWriter(new FileWriter(volunteerList4, false)); //This will delete the data in group 4 file
            BufferedWriter volunteerWriterGP5 = new BufferedWriter(new FileWriter(volunteerList5, false)); //This will delete the data in group 5 file
        } catch (IOException e) {
            System.out.println("Error writing file!");
        }
    }
}

//DO NOT CHANGE THIS PACKAGE
package coursework3;

import static coursework3.FileHandler.readVolunteers;
import static coursework3.FileHandler.storeVolunteers;
import cw3interfaces.SkillSorterInterface;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.ListIterator;

//@author sahandsabour (1614650)
//DO NOT CHANGE THIS NAME

public class SkillSorter implements SkillSorterInterface {

    private ArrayList<CommunityGroup> myGroups = new ArrayList<>(); //An arraylist to hold the community groups( groups 1-5)
    ArrayList<Volunteer> Group1 = new ArrayList<>(); //The first arraylist to hold volunteers
    ArrayList<Volunteer> Group2 = new ArrayList<>(); //The second arraylist to hold volunteers
    ArrayList<Volunteer> Group3 = new ArrayList<>(); //The third arraylist to hold volunteers
    ArrayList<Volunteer> Group4 = new ArrayList<>(); //The fourth arraylist to hold volunteers
    ArrayList<Volunteer> Group5 = new ArrayList<>(); //The fifth arraylist to hold volunteers
    CommunityGroup CG1 = new CommunityGroup(Group1); //A communityGroup object made from group1 so that we can use the CommunityGroup class methods on it
    CommunityGroup CG2 = new CommunityGroup(Group2); //A communityGroup object made from group1 so that we can use the CommunityGroup class methods on it
    CommunityGroup CG3 = new CommunityGroup(Group3); //A communityGroup object made from group1 so that we can use the CommunityGroup class methods on it
    CommunityGroup CG4 = new CommunityGroup(Group4); //A communityGroup object made from group1 so that we can use the CommunityGroup class methods on it
    CommunityGroup CG5 = new CommunityGroup(Group5); //A communityGroup object made from group1 so that we can use the CommunityGroup class methods on it

    //COMPLETE THIS CLASS
    public SkillSorter() { //This is the constructor for this class

    }

// DO NOT CHANGE ANY OF THESE METHOD NAMES, RETURN VALUES, OR ARGUMENTS
    @Override
    public void addVolunteer(Volunteer vol) {
        //add a volunteer to a Community Group USING YOUR SORTING ALGORITHM

        myGroups = getCommunityGroups(); //We add all the community groups to myGroups here by calling getCommunityGroups methode

        String skillSet = vol.getSkillSet(); //We get the skillset of the input voluteer by calling the getSkillSet methode from Volunteer class

        int minA = 0; //A variable to hold the minimum value of skill A amongst the 5 community groups
        int minB = 0; //A variable to hold the minimum value of skill B amongst the 5 community groups
        int minC = 0; //A variable to hold the minimum value of skill C amongst the 5 community groups
        int minD = 0; //A variable to hold the minimum value of skill D amongst the 5 community groups
        int minE = 0; //A variable to hold the minimum value of skill E amongst the 5 community groups
        int minAIndex = 0; //A variable to hold the index of the group with the lowest A
        int minBIndex = 0; //A variable to hold the index of the group with the lowest B
        int minCIndex = 0; //A variable to hold the index of the group with the lowest C
        int minDIndex = 0; //A variable to hold the index of the group with the lowest D
        int minEIndex = 0; //A variable to hold the index of the group with the lowest E
        int minSize = 0; //A variable to hold the minimum size of a group amongst the 5 community groups
        int minSizeIndex = 0; //A variable to hold the index of the group with the smallest size
        int equalSkills = 0; //A variable to count the number of community groups with the same number of skills
        int equalSize = 0; //A variable to count the number of community groups with the same size
        
        ArrayList<CommunityGroup> temp = new ArrayList<>(); //A temporary arraylist to store the groups that lack the same skills
        ArrayList<CommunityGroup> temp1 = new ArrayList<>(); //A temporary arraylist to store the groups that share the same size (when size= minimum size)
        
        //The following if conditions make up the sorting process of this program
        //In the first 5 if conditions, we will add a volunteer to each group starting from group 1 until we have no empty groups. 
        //then we start sorting for the input volunteers
        
        if ((Group1.isEmpty()) && (Group2.isEmpty()) && (Group3.isEmpty()) && (Group4.isEmpty()) && (Group5.isEmpty())) {
            Group1.add(vol);
            System.out.println(CG1.getSkillsTotals());
        } else if ((!Group1.isEmpty()) && (Group2.isEmpty()) && (Group3.isEmpty()) && (Group4.isEmpty()) && (Group5.isEmpty())) {
            Group2.add(vol);
            System.out.println(CG2.getSkillsTotals());
        } else if ((!Group1.isEmpty()) && (!Group2.isEmpty()) && (Group3.isEmpty()) && (Group4.isEmpty()) && (Group5.isEmpty())) {
            Group3.add(vol);
            System.out.println(CG3.getSkillsTotals());
        } else if ((!Group1.isEmpty()) && (!Group2.isEmpty()) && (!Group3.isEmpty()) && (Group4.isEmpty()) && (Group5.isEmpty())) {
            Group4.add(vol);
            System.out.println(CG4.getSkillsTotals());
        } else if ((!Group1.isEmpty()) && (!Group2.isEmpty()) && (!Group3.isEmpty()) && (!Group4.isEmpty()) && (Group5.isEmpty())) {
            Group5.add(vol);
            System.out.println(CG5.getSkillsTotals());
        } else if ((!Group1.isEmpty()) && (!Group2.isEmpty()) && (!Group3.isEmpty()) && (!Group4.isEmpty()) && (!Group5.isEmpty())) {

            for (int i = 0; i < 5; i++) {
                //This is to find minimum number of skill A and the index of the group with lowest A
                
                int[] totalA = new int[5];

                for (int a = 0; a < 5; a++) {
                    totalA[a] = myGroups.get(a).getTotalA();
                }
                Arrays.sort(totalA);

                minA = totalA[0];
                for (int n = 4; n >= 0; n--) {
                    if (myGroups.get(n).getTotalA() == minA) {
                        minAIndex = n;

                    } else {

                    }
                }
                
                //This is to find minimum number of skill B and the index of the group with lowest B
                int[] totalB = new int[5];

                for (int b = 0; b < 5; b++) {
                    totalB[b] = myGroups.get(b).getTotalB();
                }
                Arrays.sort(totalB);

                minB = totalB[0];
                for (int n = 4; n >= 0; n--) {
                    if (myGroups.get(n).getTotalB() == minB) {
                        minBIndex = n;

                    } else {

                    }
                }
                //This is to find minimum number of skill C and the index of the group with lowest C
                int[] totalC = new int[5];

                for (int c = 0; c < 5; c++) {
                    totalC[c] = myGroups.get(c).getTotalC();
                }
                Arrays.sort(totalC);

                minC = totalC[0];
                for (int n = 4; n >= 0; n--) {
                    if (myGroups.get(n).getTotalC() == minC) {
                        minCIndex = n;

                    } else {

                    }
                }
                //This is to find minimum number of skill D and the index of the group with lowest D
                int[] totalD = new int[5];

                for (int d = 0; d < 5; d++) {
                    totalD[d] = myGroups.get(d).getTotalD();
                }
                Arrays.sort(totalD);

                minD = totalD[0];
                for (int n = 4; n >= 0; n--) {
                    if (myGroups.get(n).getTotalD() == minD) {
                        minDIndex = n;

                    } else {

                    }
                }
                //This is to find minimum number of skill E and the index of the group with lowest E
                int[] totalE = new int[5];

                for (int e = 0; e < 5; e++) {
                    totalE[e] = myGroups.get(e).getTotalE();
                }
                Arrays.sort(totalE);

                minE = totalE[0];
                for (int n = 4; n >= 0; n--) {
                    if (myGroups.get(n).getTotalE() == minE) {
                        minEIndex = n;

                    } else {

                    }
                }
                //This is to find minimum size and the index of the group with lowest size
                int[] totalSize = new int[5];

                for (int s = 0; s < 5; s++) {
                    totalSize[s] = myGroups.get(s).howManyVolunteers();
                }
                Arrays.sort(totalSize);

                minSize = totalSize[0];

                for (int n = 4; n >= 0; n--) {
                    if (myGroups.get(n).howManyVolunteers() == minSize) {
                        minSizeIndex = n;

                    } else {

                    }
                }

            }
            //Now the algorithm works as follows:
            //If the input skillset contains a repeated letter, the program searches for the group that lacks that letter and adds the volunteer to that group
            if (skillSet.contains("AA") || skillSet.contains("AAA")) {
                addA(minA, minAIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);

            } else if (skillSet.contains("BB") || skillSet.contains("BBB")) {
                addB(minB, minBIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
            } else if (skillSet.contains("CC") || skillSet.contains("CCC")) {
                addC(minC, minCIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
            } else if (skillSet.contains("DD") || skillSet.contains("DDD")) {
                addD(minD, minDIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
            } else if (skillSet.contains("EE") || skillSet.contains("EEE")) {
                addE(minE, minEIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
            } 
            //If the input doesn't contain a repeated letter, there will be 10 possible choices left as follows:
            //In each of these situations, minimum of each letter in the skillset is compared with the others.
            //Then the letter with the smallest minimum is chosen as a leader for that skillset and the volunteer will be added to a group that lacks the leader skill
            else {
                if (skillSet.equals("ABC")) {
                    if (minA < minB) {
                        if (minA < minC) { //If A is the smallest
                            addA(minA, minAIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        } else { //If C is the smallest
                            addC(minC, minCIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        }
                    } else {
                        if (minB < minC) { //If B is the smallest
                            addB(minB, minBIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        } else { //If C is the smallest
                            addC(minC, minCIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        }
                    }
                } else if (skillSet.equals("ABD")) {
                    if (minA < minB) {
                        if (minA < minD) { //If A is the smallest
                            addA(minA, minAIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        } else { //If D is the smallest
                            addD(minD, minDIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        }
                    } else {
                        if (minB < minD) { //If B is the smallest
                            addB(minB, minBIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        } else { //If D is the smallest
                            addD(minD, minDIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        }
                    }
                } else if (skillSet.equals("ABE")) {
                    if (minA < minB) {
                        if (minA < minE) { //If A is the smallest
                            addA(minA, minAIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        } else { //If E is the smallest
                            addE(minE, minEIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        }
                    } else {
                        if (minB < minE) { //If B is the smallest
                            addB(minB, minBIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        } else { //If E is the smallest
                            addE(minE, minEIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        }
                    }
                } else if (skillSet.equals("ACD")) {
                    if (minA < minC) {
                        if (minA < minD) { //If A is the smallest
                            addA(minA, minAIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        } else { //If D is the smallest
                            addD(minD, minDIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        }
                    } else {
                        if (minC < minD) { //If C is the smallest
                            addC(minC, minCIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        } else { //If D is the smallest
                            addD(minD, minDIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        }
                    }
                } else if (skillSet.equals("ACE")) {
                    if (minA < minC) {
                        if (minA < minE) { //If A is the smallest
                            addA(minA, minAIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        } else { //If E is the smallest
                            addE(minE, minEIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        }
                    } else {
                        if (minC < minE) { //If C is the smallest
                            addC(minC, minCIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        } else { //If E is the smallest
                            addE(minE, minEIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        }
                    }
                } else if (skillSet.equals("ADE")) {
                    if (minA < minD) {
                        if (minA < minE) { //If A is the smallest
                            addA(minA, minAIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        } else { //If E is the smallest
                            addE(minE, minEIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        }
                    } else {
                        if (minD < minE) { //If D is the smallest
                            addD(minD, minDIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        } else { //If E is the smallest
                            addE(minE, minEIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        }
                    }
                } else if (skillSet.equals("BCD")) {
                    if (minB < minC) {
                        if (minB < minD) { //If B is the smallest
                            addB(minB, minBIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        } else { //If D is the smallest
                            addD(minD, minDIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        }
                    } else {
                        if (minC < minD) { //If C is the smallest
                            addC(minC, minCIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        } else { //If D is the smallest
                            addD(minD, minDIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        }
                    }
                } else if (skillSet.equals("BCE")) {
                    if (minB < minC) {
                        if (minB < minE) { //If B is the smallest
                            addB(minB, minBIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        } else { //If E is the smallest
                            addE(minE, minEIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        }
                    } else {
                        if (minC < minE) { //If C is the smallest
                            addC(minC, minCIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        } else { //If E is the smallest
                            addE(minE, minEIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        }
                    }
                } else if (skillSet.equals("BDE")) {
                    if (minB < minD) {
                        if (minB < minE) { //If B is the smallest
                            addB(minB, minBIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        } else { //If E is the smallest
                            addE(minE, minEIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        }
                    } else {
                        if (minD < minE) { //If D is the smallest
                            addD(minD, minDIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        } else { //If E is the smallest
                            addE(minE, minEIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        }
                    }
                } else if (skillSet.equals("CDE")) {
                    if (minC < minD) {
                        if (minC < minE) { //If C is the smallest
                            addC(minC, minCIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        } else { //If E is the smallest
                            addE(minE, minEIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        }
                    } else {
                        if (minD < minE) { //If D is the smallest
                            addD(minD, minDIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        } else { //If E is the smallest
                            addE(minE, minEIndex, minSize, minSizeIndex, vol, myGroups, temp, temp1);
                        }
                    }
                }

            }
        }

        System.out.println("Group 1 now has " + Group1.size() + " volunteers."); //This is for printing how many volunteers are inside group 1
        System.out.println("Group 2 now has " + Group2.size() + " volunteers."); //This is for printing how many volunteers are inside group 2
        System.out.println("Group 3 now has " + Group3.size() + " volunteers."); //This is for printing how many volunteers are inside group 3
        System.out.println("Group 4 now has " + Group4.size() + " volunteers."); //This is for printing how many volunteers are inside group 4
        System.out.println("Group 5 now has " + Group5.size() + " volunteers.\n"); //This is for printing how many volunteers are inside group 5

    }

    @Override
    public void moveVolunteer(String skillSet, CommunityGroup from, CommunityGroup to) {
        //move a volunteer with this skillset (eg AAA, BCD) from one CommunityGroup to another
        //COMPLETE CODE HERE
        ArrayList<Volunteer> moveFrom = new ArrayList<>(); //An arraylist to store the volunteers of the group that we move a volunteer from
        ArrayList<Volunteer> moveTo = new ArrayList<>(); //An arraylist to store the volunteers of the group that we move a volunteer to
        moveFrom = from.getVols(); //To get the volunteers of the mentioned group inside the mentioned arraylist
        String empty = ""; //A string to print a message when it's necessary (input volunteer doesn't exist)
        
        //We iterate through the volunteers in order to find the volunteer with the same skillset as input
        ListIterator<Volunteer> moveOneIterator = moveFrom.listIterator(); //A list iterator to go through the arraylist moveFrom
        while (moveOneIterator.hasNext()) {
            Volunteer vol = moveOneIterator.next();
            if (vol.getSkillSet().equals(skillSet)) {

                moveOneIterator.remove(); //We remove the volunteer from the first group

                moveTo = to.getVols();
                Volunteer vol1 = new Volunteer(skillSet); //We create a new volunteer with the same skillset as the removed volunteer
                moveTo.add(vol1); //We add the new volunteer to the second group
                System.out.println("The Volunteer " + skillSet + " has been moved!");
                return;
            } else {
                empty = "The mentiond Volunteer doesn't exist in the mentioned group";

            }

        }
        System.out.println(empty); //This will print a text if the input volunteer does not exist in the input group

    }

    @Override
    public void deleteVolunteer(String skillSet, CommunityGroup from) {
        //delete a volunteer with this skillset from this CommunityGroup

        String empty = ""; //A string to print a message when it's necessary (input volunteer doesn't exist)
        ArrayList<Volunteer> deleteVolunteer = new ArrayList<>(); //An arraylist to store the volunteers of the group that we remove a volunteer from
        deleteVolunteer = from.getVols(); //To store the volunteers of the mentioned group
        //We iterate through the volunteers in order to find the volunteer with the same skillset as input
        ListIterator<Volunteer> deleteOneIterator = deleteVolunteer.listIterator(); //A list iterator to go through the arraylist deleteVolunteer
        while (deleteOneIterator.hasNext()) {
            Volunteer vol = deleteOneIterator.next();
            if (vol.getSkillSet().equals(skillSet)) {
                deleteOneIterator.remove(); //We remove the volunteer from the group
                System.out.println("The Volunteer " + skillSet + " has been removed!");
                return;
            } else {
                empty = "The mentiond Volunteer doesn't exist in the mentioned group";

            }

        }
        System.out.println(empty); //This will print a text if the input volunteer does not exist in the input group
    }

    @Override
    public void deleteAllVolunteers() {
        //Here we iterate through each of the community groups to delete all their volunteers one by one
        
        ListIterator<Volunteer> deleteGroup1 = Group1.listIterator(); //A list iterator to go through Group1
        Volunteer vol;
        while (deleteGroup1.hasNext()) {
            vol = deleteGroup1.next();
            deleteGroup1.remove();
        }
        ListIterator deleteGroup2 = Group2.listIterator(); //A list iterator to go through Group2
        while (deleteGroup2.hasNext()) {
            vol = (Volunteer) deleteGroup2.next();
            deleteGroup2.remove();
        }
        ListIterator deleteGroup3 = Group3.listIterator(); //A list iterator to go through Group3
        while (deleteGroup3.hasNext()) {
            vol = (Volunteer) deleteGroup3.next();
            deleteGroup3.remove();
        }
        ListIterator deleteGroup4 = Group4.listIterator(); //A list iterator to go through Group4
        while (deleteGroup4.hasNext()) {
            vol = (Volunteer) deleteGroup4.next();
            deleteGroup4.remove();
        }
        ListIterator deleteGroup5 = Group5.listIterator(); //A list iterator to go through Group5
        while (deleteGroup5.hasNext()) {
            vol = (Volunteer) deleteGroup5.next();
            deleteGroup5.remove();
        }

        System.out.println("All the Volunteers have been deleted!");
    }

    @Override
    public ArrayList<CommunityGroup> getCommunityGroups() {
        //return an ArrayList of all this application's CommunityGroups
        myGroups.add(CG1); //To add the community group object made of Group1 to myGroups
        myGroups.add(CG2); //To add the community group object made of Group2 to myGroups
        myGroups.add(CG3); //To add the community group object made of Group3 to myGroups
        myGroups.add(CG4); //To add the community group object made of Group4 to myGroups
        myGroups.add(CG5); //To add the community group object made of Group5 to myGroups

        return myGroups;
    }

    public ArrayList<Volunteer> getVolunteers(int groupNum) { //This will return an arraylist of each community group's volunteers
        ArrayList<Volunteer> Temp = new ArrayList<>(); //A temporary arraylist to store the volunteers of each community group (based on int groupnum, where groupNum is the number of the group)
        if (groupNum == 1) {
            Temp = Group1;
        }
        if (groupNum == 2) {
            Temp = Group2;
        }
        if (groupNum == 3) {
            Temp = Group3;
        }
        if (groupNum == 4) {
            Temp = Group4;
        }
        if (groupNum == 5) {
            Temp = Group5;
        }
        return Temp;
    }

    public void displayAllVolunteers() {

        ArrayList<Volunteer> storeVolunteers = new ArrayList<>(); //To create an arraylist to store the volunteers of each community group
        Volunteer volunteer; //A volunteer object to represent the volunteers present in each community group one by one
        storeVolunteers = getVolunteers(1); //To store the volunteers of Group1 inside storeVolunteers
        ListIterator showingVolGroup1 = storeVolunteers.listIterator(); //To iterate through storeVolunteers when it stores Group1 volunteers and print each volunteer
        System.out.println("Group 1 Contains the following Volunteers:");
        while (showingVolGroup1.hasNext()) {
            volunteer = (Volunteer) showingVolGroup1.next();
            System.out.println(volunteer.getSkillSet());
        }
        System.out.println("Total Volunteers: " + CG1.howManyVolunteers());
        System.out.println("Total skills: \n" + CG1.getSkillsTotals());
        System.out.println("\n=================================================\n");

        storeVolunteers = getVolunteers(2); //To store the volunteers of Group2 inside storeVolunteers
        ListIterator showingVolGroup2 = storeVolunteers.listIterator(); //To iterate through storeVolunteers when it stores Group2 volunteers and print each volunteer
        System.out.println("Group 2 Contains the following Volunteers:");
        while (showingVolGroup2.hasNext()) {
            volunteer = (Volunteer) showingVolGroup2.next();
            System.out.println(volunteer.getSkillSet());

        }
        System.out.println("Total Volunteers: " + CG2.howManyVolunteers());
        System.out.println("Total skills: \n" + CG2.getSkillsTotals());
        System.out.println("\n=================================================\n");

        storeVolunteers = getVolunteers(3); //To store the volunteers of Group3 inside storeVolunteers
        ListIterator showingVolGroup3 = storeVolunteers.listIterator(); //To iterate through storeVolunteers when it stores Group3 volunteers and print each volunteer
        System.out.println("Group 3 Contains the following Volunteers:");
        while (showingVolGroup3.hasNext()) {
            volunteer = (Volunteer) showingVolGroup3.next();
            System.out.println(volunteer.getSkillSet());

        }
        System.out.println("Total Volunteers: " + CG3.howManyVolunteers());
        System.out.println("Total skills: \n" + CG3.getSkillsTotals());
        System.out.println("\n=================================================\n");

        storeVolunteers = getVolunteers(4); //To store the volunteers of Group4 inside storeVolunteers
        ListIterator showingVolGroup4 = storeVolunteers.listIterator(); //To iterate through storeVolunteers when it stores Group4 volunteers and print each volunteer
        System.out.println("Group 4 Contains the following Volunteers:");
        while (showingVolGroup4.hasNext()) {
            volunteer = (Volunteer) showingVolGroup4.next();
            System.out.println(volunteer.getSkillSet());

        }
        System.out.println("Total Volunteers: " + CG4.howManyVolunteers());
        System.out.println("Total skills: \n" + CG4.getSkillsTotals());
        System.out.println("\n=================================================\n");

        storeVolunteers = getVolunteers(5); //To store the volunteers of Group5 inside storeVolunteers
        ListIterator showingVolGroup5 = storeVolunteers.listIterator(); //To iterate through storeVolunteers when it stores Group4 volunteers and print each volunteer
        System.out.println("Group 5 Contains the following Volunteers:");
        while (showingVolGroup5.hasNext()) {
            volunteer = (Volunteer) showingVolGroup5.next();
            System.out.println(volunteer.getSkillSet());

        }
        System.out.println("Total Volunteers: " + CG5.howManyVolunteers());
        System.out.println("Total skills: \n" + CG5.getSkillsTotals());
        System.out.println("\n=================================================\n");

    }

    public void saveVolunteers() {

        storeVolunteers(Group1, 1); //To save the volunteers of Group1 inside a file
        storeVolunteers(Group2, 2); //To save the volunteers of Group2 inside a file
        storeVolunteers(Group3, 3); //To save the volunteers of Group3 inside a file
        storeVolunteers(Group4, 4); //To save the volunteers of Group4 inside a file
        storeVolunteers(Group5, 5); //To save the volunteers of Group5 inside a file

    }

    public void readVolunteersfromFile() { //This is to restore the volunteers to their groups after restarting the program
        ArrayList<Volunteer> Volunteers = new ArrayList<>(); //A temporary arraylist to store the volunteers of a community group
        Volunteers = readVolunteers(1); //To store volunteers of group1 inside the temporary arraylist
        ListIterator<Volunteer> getVol1 = Volunteers.listIterator(); //We iterate through the volunteers and add them to Group1 one by one (restoring volunteers)
        while (getVol1.hasNext()) {
            Volunteer vol = getVol1.next();
            if (vol.getSkillSet() != "Skill A: 0, Skill B: 0, Skill C: 0, Skill D: 0, Skill E: 0") {
                Group1.add(vol);
            }
        }

        Volunteers = readVolunteers(2); //To store volunteers of group2 inside the temporary arraylist
        ListIterator<Volunteer> getVol2 = Volunteers.listIterator(); //We iterate through the volunteers and add them to Group2 one by one (restoring volunteers)
        while (getVol2.hasNext()) {
            Volunteer vol = getVol2.next();
            if (vol.getSkillSet() != "Skill A: 0, Skill B: 0, Skill C: 0, Skill D: 0, Skill E: 0") { //To avoid adding blank to the group
                Group2.add(vol);
            }
        }

        Volunteers = readVolunteers(3); //To store volunteers of group3 inside the temporary arraylist
        ListIterator<Volunteer> getVol3 = Volunteers.listIterator(); //We iterate through the volunteers and add them to Group3 one by one (restoring volunteers)
        while (getVol3.hasNext()) {
            Volunteer vol = getVol3.next();
            if (vol.getSkillSet() != "Skill A: 0, Skill B: 0, Skill C: 0, Skill D: 0, Skill E: 0") { //To avoid adding blank to the group
                Group3.add(vol);
            }
        }

        Volunteers = readVolunteers(4); //To store volunteers of group4 inside the temporary arraylist
        ListIterator<Volunteer> getVol4 = Volunteers.listIterator(); //We iterate through the volunteers and add them to Group4 one by one (restoring volunteers)
        while (getVol4.hasNext()) {
            Volunteer vol = getVol4.next();
            if (vol.getSkillSet() != "Skill A: 0, Skill B: 0, Skill C: 0, Skill D: 0, Skill E: 0") { //To avoid adding blank to the group
                Group4.add(vol);
            }
        }

        Volunteers = readVolunteers(5); //To store volunteers of group5 inside the temporary arraylist
        ListIterator<Volunteer> getVol5 = Volunteers.listIterator(); //We iterate through the volunteers and add them to Group5 one by one (restoring volunteers)
        while (getVol5.hasNext()) {
            Volunteer vol = getVol5.next();
            if (vol.getSkillSet() != "Skill A: 0, Skill B: 0, Skill C: 0, Skill D: 0, Skill E: 0") { //To avoid adding blank to the group
                Group5.add(vol);
            }
        }
    }

    public static void addA(int minA, int minAIndex, int minSize, int minSizeIndex, Volunteer vol, ArrayList<CommunityGroup> myGroups, ArrayList<CommunityGroup> temp, ArrayList<CommunityGroup> temp1) {

        int equalSkills = 0; //A variable to count the number of community groups lacking the same skills
        int equalSize = 0; //A variable to count the number of community groups with the same size (when size=minimum size)
        for (int i = 0; i < 5; i++) {

            if (minA == myGroups.get(i).getTotalA()) { //To find the number groups that lack skill A
                equalSkills = equalSkills + 1;
                temp.add(myGroups.get(i)); //We add the groups lacking skill A to temp arraylist
            } else {

            }
        }

        if (equalSkills > 1) { //If we have more than one group lacking Skill A
            ListIterator<CommunityGroup> tempList = temp.listIterator();
            int i = -1;
            while (tempList.hasNext()) {
                i++;
                //System.out.println("min size here is "+minSize);
                if (minSize == tempList.next().howManyVolunteers()) { //To find the number of groups with the same size
                    equalSize = equalSize + 1;
                    //System.out.println("the groups lacking size: "+equalSkills);
                    //System.out.println("the groups lacking size is group : "+i);
                    temp1.add(temp.get(i)); //We add the groups with the same size into temp1 arraylist
                } else {

                }

            }
            if (equalSize > 1) { //If there are more than one group with minimum size, then the volunteer is added to the group with the smaller index
                temp1.get(0).allVolunteers.add(vol);

            } else { //If there's only one group with minimum size, then we will add the volunteer to that group
                //System.out.println("Only one group has min size");
                myGroups.get(minSizeIndex).allVolunteers.add(vol);
            }
        } else { //If there's only one group that lacks A, we will add A to that group
            //System.out.println("Only one group lacking A");
            myGroups.get(minAIndex).allVolunteers.add(vol);
        }
    }

    public static void addB(int minB, int minBIndex, int minSize, int minSizeIndex, Volunteer vol, ArrayList<CommunityGroup> myGroups, ArrayList<CommunityGroup> temp, ArrayList<CommunityGroup> temp1) {

        int equalSkills = 0; //A variable to count the number of community groups lacking the same skills
        int equalSize = 0; //A variable to count the number of community groups with the same size (when size=minimum size)
        for (int i = 0; i < 5; i++) {

            if (minB == myGroups.get(i).getTotalB()) { //To find the number groups that lack skill B
                equalSkills = equalSkills + 1;
                temp.add(myGroups.get(i)); //We add the groups lacking skill B to temp arraylist
            } else {

            }
        }

        if (equalSkills > 1) { //If we have more than one group lacking Skill B
            ListIterator<CommunityGroup> tempList = temp.listIterator();
            int i = -1;
            while (tempList.hasNext()) {
                i++;

                if (minSize == tempList.next().howManyVolunteers()) { //To find the number of groups with the same size
                    equalSize = equalSize + 1;
                    temp1.add(temp.get(i)); //We add the groups with the same size into temp1 arraylist
                } else {

                }

            }

            if (equalSize > 1) { //If there are more than one group with minimum size, then the volunteer is added to the group with the smaller index
                temp1.get(0).allVolunteers.add(vol);

            } else if (equalSize == 1) { //If there's only one group with minimum size, then we will add the volunteer to that group
                //System.out.println("Only one group has min size");
                myGroups.get(minSizeIndex).allVolunteers.add(vol);
            }
        } else { //If there's only one group that lacks A, we will add B to that group
            //System.out.println("Only one group lacking B");

            myGroups.get(minBIndex).allVolunteers.add(vol);
        }
    }

    public static void addC(int minC, int minCIndex, int minSize, int minSizeIndex, Volunteer vol, ArrayList<CommunityGroup> myGroups, ArrayList<CommunityGroup> temp, ArrayList<CommunityGroup> temp1) {

        int equalSkills = 0; //A variable to count the number of community groups lacking the same skills
        int equalSize = 0; //A variable to count the number of community groups with the same size (when size=minimum size)
        for (int i = 0; i < 5; i++) {

            if (minC == myGroups.get(i).getTotalC()) { //To find the number groups that lack skill C
                equalSkills = equalSkills + 1;

                temp.add(myGroups.get(i)); //We add the groups lacking skill C to temp arraylist
            } else {

            }
        }

        if (equalSkills > 1) { //If we have more than one group lacking Skill C
            ListIterator<CommunityGroup> tempList = temp.listIterator();
            int i = -1;
            while (tempList.hasNext()) {
                i++;
                //System.out.println("min size here is "+minSize);
                if (minSize == tempList.next().howManyVolunteers()) { //To find the number of groups with the same size
                    equalSize = equalSize + 1;
                    //System.out.println("the groups lacking size: "+equalSkills);
                    //System.out.println("the groups lacking size is group : "+i);
                    temp1.add(temp.get(i)); //We add the groups with the same size into temp1 arraylist
                } else {

                }

            }
            if (equalSize > 1) { //If there are more than one group with minimum size, then the volunteer is added to the group with the smaller index
                temp1.get(0).allVolunteers.add(vol);

            } else { //If there's only one group with minimum size, then we will add the volunteer to that group
                //System.out.println("Only one group has min size");
                myGroups.get(minSizeIndex).allVolunteers.add(vol);
            }
        } else { //If there's only one group that lacks C, we will add A to that group
            //System.out.println("Only one group lacking C");
            myGroups.get(minCIndex).allVolunteers.add(vol);
        }
    }

    public static void addD(int minD, int minDIndex, int minSize, int minSizeIndex, Volunteer vol, ArrayList<CommunityGroup> myGroups, ArrayList<CommunityGroup> temp, ArrayList<CommunityGroup> temp1) {

        int equalSkills = 0;//A variable to count the number of community groups lacking the same skills
        int equalSize = 0; //A variable to count the number of community groups with the same size (when size=minimum size)

        for (int i = 0; i < 5; i++) {

            if (minD == myGroups.get(i).getTotalD()) { //To find the number groups that lack skill D
                equalSkills = equalSkills + 1;

                temp.add(myGroups.get(i)); //We add the groups lacking skill D to temp arraylist
            } else {

            }
        }

        if (equalSkills > 1) { //If we have more than one group lacking Skill D
            ListIterator<CommunityGroup> tempList = temp.listIterator();
            int i = -1;
            while (tempList.hasNext()) {
                i++;
                //System.out.println("min size here is "+minSize);
                if (minSize == tempList.next().howManyVolunteers()) { //To find the number of groups with the same size
                    equalSize = equalSize + 1;
                    //System.out.println("the groups lacking size: "+equalSkills);
                    //System.out.println("the groups lacking size is group : "+i);
                    temp1.add(temp.get(i)); //We add the groups with the same size into temp1 arraylist
                } else {

                }

            }
            if (equalSize > 1) { //If there are more than one group with minimum size, then the volunteer is added to the group with the smaller index
                temp1.get(0).allVolunteers.add(vol);

            } else { //If there's only one group with minimum size, then we will add the volunteer to that group
                //System.out.println("Only one group has min size");
                myGroups.get(minSizeIndex).allVolunteers.add(vol);
            }
        } else { //If there's only one group that lacks D, we will add A to that group
            //System.out.println("Only one group lacking D");
            myGroups.get(minDIndex).allVolunteers.add(vol);
        }
    }

    public static void addE(int minE, int minEIndex, int minSize, int minSizeIndex, Volunteer vol, ArrayList<CommunityGroup> myGroups, ArrayList<CommunityGroup> temp, ArrayList<CommunityGroup> temp1) {

        int equalSkills = 0; //A variable to count the number of community groups lacking the same skills
        int equalSize = 0; //A variable to count the number of community groups with the same size (when size=minimum size)
        for (int i = 0; i < 5; i++) {

            if (minE == myGroups.get(i).getTotalE()) { //To find the number groups that lack skill E
                equalSkills = equalSkills + 1;
                temp.add(myGroups.get(i)); //We add the groups lacking skill E to temp arraylist
            } else {

            }
        }

        if (equalSkills > 1) { //If we have more than one group lacking Skill E
            ListIterator<CommunityGroup> tempList = temp.listIterator();
            int i = -1;
            while (tempList.hasNext()) {
                i++;
                //System.out.println("min size here is "+minSize);
                if (minSize == tempList.next().howManyVolunteers()) { //To find the number of groups with the same size
                    equalSize = equalSize + 1;
                    //System.out.println("the groups lacking size: "+equalSkills);
                    //System.out.println("the groups lacking size is group : "+i);
                    temp1.add(temp.get(i)); //We add the groups with the same size into temp1 arraylist
                } else {

                }

            }
            if (equalSize > 1) { //If there are more than one group with minimum size, then the volunteer is added to the group with the smaller index
                temp1.get(0).allVolunteers.add(vol);

            } else { //If there's only one group with minimum size, then we will add the volunteer to that group
                //System.out.println("Only one group has min size");
                myGroups.get(minSizeIndex).allVolunteers.add(vol);
            }
        } else { //If there's only one group that lacks E, we will add A to that group
            //System.out.println("Only one group lacking E");
            myGroups.get(minEIndex).allVolunteers.add(vol);
        }
    }

}

//DO NOT CHANGE THIS PACKAGE
package coursework3;

import cw3interfaces.CommunityGroupInterface;
import java.util.ArrayList;
import java.util.ListIterator;
//@author sahandsabour (1614650)
//DO NOT CHANGE THIS NAME
public class CommunityGroup implements CommunityGroupInterface {

    ArrayList<Volunteer> allVolunteers = new ArrayList<>();
    int numA = 0; //This is a variable to hold the number of skill As inside a group or a skillset
    int numB = 0; //This is a variable to hold the number of skill Bs inside a group or a skillset
    int numC = 0; //This is a variable to hold the number of skill Cs inside a group or a skillset
    int numD = 0; //This is a variable to hold the number of skill Ds inside a group or a skillset
    int numE = 0; //This is a variable to hold the number of skill Es inside a group or a skillset

// DO NOT CHANGE ANY OF THESE METHOD NAMES, RETURN VALUES, OR ARGUMENTS   
    public CommunityGroup(ArrayList<Volunteer> vol) {

        this.allVolunteers = vol;
    }

    @Override
    public int howManyVolunteers() {
        //return the total number of volunteers in this community group

        int allVolunteersNum = 0;
        ListIterator allVolunteersNumIterator = allVolunteers.listIterator();
        while (allVolunteersNumIterator.hasNext()) {
            allVolunteersNumIterator.next();
            allVolunteersNum = allVolunteersNum + 1;

        }
        //System.out.println(allVolunteersNum + " volunteers in this group");
        return allVolunteersNum;
    }

    @Override
    public String getSkillsTotals() {
        //This is to get the total number of skills inside a community group
        numA = 0; //To reset the value of this variable 
        numB = 0; //To reset the value of this variable 
        numC = 0; //To reset the value of this variable 
        numD = 0; //To reset the value of this variable 
        numE = 0; //To reset the value of this variable 
        ListIterator allVolunteersSkillsIterator = allVolunteers.listIterator();
        while (allVolunteersSkillsIterator.hasNext()) {
            Volunteer singleVolunteer = (Volunteer) allVolunteersSkillsIterator.next();
            String skill = singleVolunteer.getSkillSet();
            numA = getSkillA(skill);
            numB = getSkillB(skill);
            numC = getSkillC(skill);
            numD = getSkillD(skill);
            numE = getSkillE(skill);

        }

        return "Skill A: " + numA + ", Skill B: " + numB + ", Skill C: " + numC + ", Skill D: " + numD + ", Skill E: " + numE;
    }

    public int getSkillA(String skill) { //This is to get the number of A skills of a skillset 

        if (skill.contains("AAA")) {
            numA = numA + 3;
        } else if (skill.contains("AA")) {
            numA = numA + 2;
        } else if (skill.contains("A")) {
            numA++;
        }

        return numA;
    }

    public int getSkillB(String skill) { //This is to get the number of B skills of a skillset 

        if (skill.contains("BBB")) {
            numB = numB + 3;
        } else if (skill.contains("BB")) {
            numB = numB + 2;
        } else if (skill.contains("B")) {
            numB++;
        }
        return numB;
    }

    public int getSkillC(String skill) { //This is to get the number of C skills of a skillset 
        if (skill.contains("CCC")) {
            numC = numC + 3;
        } else if (skill.contains("CC")) {
            numC = numC + 2;
        } else if (skill.contains("C")) {
            numC++;
        }
        return numC;
    }

    public int getSkillD(String skill) { //This is to get the number of D skills of a skillset  

        if (skill.contains("DDD")) {
            numD = numD + 3;
        } else if (skill.contains("DD")) {
            numD = numD + 2;
        } else if (skill.contains("D")) {
            numD++;
        }
        return numD;
    }

    public int getSkillE(String skill) { //This is to get the number of E skills of a skillset  

        if (skill.contains("EEE")) {
            numE = numE + 3;
        } else if (skill.contains("EE")) {
            numE = numE + 2;
        } else if (skill.contains("E")) {
            numE++;
        }
        return numE;
    }

    public int getTotalA() { //This is to get the total number of A skills inside a community group
        numA = 0; //To reset the value of this variable 
        ListIterator allVolunteersSkillsIterator = allVolunteers.listIterator();
        //We iterate thorugh the volunteers list (including volunteers of a group to find the total number of As
        while (allVolunteersSkillsIterator.hasNext()) {
            Volunteer singleVolunteer = (Volunteer) allVolunteersSkillsIterator.next();
            String skill = singleVolunteer.getSkillSet();
            numA = getSkillA(skill);
        }
        return numA;
    }

    public int getTotalB() { //This is to get the total number of B skills inside a community group
        numB = 0; //To reset the value of this variable 
        //We iterate thorugh the volunteers list (including volunteers of a group to find the total number of Bs
        ListIterator allVolunteersSkillsIterator = allVolunteers.listIterator();
        while (allVolunteersSkillsIterator.hasNext()) {
            Volunteer singleVolunteer = (Volunteer) allVolunteersSkillsIterator.next();
            String skill = singleVolunteer.getSkillSet();
            numB = getSkillB(skill);
        }
        return numB;
    }

    public int getTotalC() { //This is to get the total number of C skills inside a community group
        numC = 0; //To reset the value of this variable 
        //We iterate thorugh the volunteers list (including volunteers of a group to find the total number of Cs
        ListIterator allVolunteersSkillsIterator = allVolunteers.listIterator();
        while (allVolunteersSkillsIterator.hasNext()) {
            Volunteer singleVolunteer = (Volunteer) allVolunteersSkillsIterator.next();
            String skill = singleVolunteer.getSkillSet();
            numC = getSkillC(skill);
        }
        return numC;
    }

    public int getTotalD() { //This is to get the total number of D skills inside a community group
        numD = 0; //To reset the value of this variable 
        //We iterate thorugh the volunteers list (including volunteers of a group to find the total number of Ds
        ListIterator allVolunteersSkillsIterator = allVolunteers.listIterator();
        while (allVolunteersSkillsIterator.hasNext()) {
            Volunteer singleVolunteer = (Volunteer) allVolunteersSkillsIterator.next();
            String skill = singleVolunteer.getSkillSet();
            numD = getSkillD(skill);
        }
        return numD;
    }

    public int getTotalE() { //This is to get the total number of E skills inside a community group
        numE = 0; //To reset the value of this variable 
        //We iterate thorugh the volunteers list (including volunteers of a group to find the total number of Es
        ListIterator allVolunteersSkillsIterator = allVolunteers.listIterator();
        while (allVolunteersSkillsIterator.hasNext()) {
            Volunteer singleVolunteer = (Volunteer) allVolunteersSkillsIterator.next();
            String skill = singleVolunteer.getSkillSet();
            numE = getSkillE(skill);
        }
        return numE;
    }

    public ArrayList<Volunteer> getVols() { //This is to get the volunteers of a CommunityGroup object as an arraylist 
        Volunteer vol;

        return allVolunteers;
    }
}

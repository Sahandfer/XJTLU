//DO NOT CHANGE THIS PACKAGE
package coursework3;

import cw3interfaces.VolunteerInterface;
//@author sahandsabour (1614650)
//DO NOT CHANGE THIS NAME
public class Volunteer implements VolunteerInterface {

    private String skills; //A varibale to hold the skillset of a volunteer

    public Volunteer(String skillSet) { //This is the constructor for the class and it gets the skillset 
        skills = skillSet; 
        skills = skillSetAlphabeticalSorter(skills); //This will use the method to alphabetically sort the input skillSet
    }

    @Override
    public String getSkillSet() { //This a method for getting the skillset of a volunteer object

        return skills;
    }

    private String skillSetAlphabeticalSorter(String skillSet) { //This is a method for alphabetically sorting the skillset, it gets a string and returns one
        String firstSkill = " "; //A variable to hold the first letter of the input skillset
        String secondSkill = " "; //A variable to hold the second letter of the input skillset
        String thirdSkill = " "; //A variable to hold the third letter of the input skillset
        String[] skillLetters = skillSet.split(""); //We split the input skillset to its letters and set each of the letters to one of the mentioned variables
        firstSkill = String.valueOf(skillLetters[0]);
        secondSkill = String.valueOf(skillLetters[1]);
        thirdSkill = String.valueOf(skillLetters[2]);
        //The following series of if conditions are for sorting the skill letters in the skillSet alphabetically
        
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
        return skillSet;
    }

}

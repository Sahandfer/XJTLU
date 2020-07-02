library(doBy)
library(ggplot2)

# Read the data for 10 consecutive days
day1<-read.csv("Datasets/nyt1.csv")
day2<-read.csv("Datasets/nyt2.csv")
day3<-read.csv("Datasets/nyt3.csv")
day4<-read.csv("Datasets/nyt4.csv")
day5<-read.csv("Datasets/nyt5.csv")
day6<-read.csv("Datasets/nyt6.csv")
day7<-read.csv("Datasets/nyt7.csv")
day8<-read.csv("Datasets/nyt8.csv")
day9<-read.csv("Datasets/nyt9.csv")
day10<-read.csv("Datasets/nyt10.csv")

# Adding a column to distinguish each day from others
day1$whichDay <- "Day1"
day2$whichDay <- "Day2"
day3$whichDay <- "Day3"
day4$whichDay <- "Day4"
day5$whichDay <- "Day5"
day6$whichDay <- "Day6"
day7$whichDay <- "Day7"
day8$whichDay <- "Day8"
day9$whichDay <- "Day9"
day10$whichDay <- "Day10"

# Storing all the 10 days' data into a sin gle variable
#allDays <- rbind(day1, day2, day3, day4, day5, day6, day7, day8, day9, day10)
allDays <- rbind(day1, day2, day3, day4, day5, day6, day7, day8, day9, day10)
#Setting the gender values to Male/Female (from 0 or 1)
allDays$Gender <- ifelse(allDays$Gender == 0, "Male", "Female")

#Calculating the Click-through-rate (CTR) for each user
allDays$CTR <- ifelse(allDays$Impressions != 0, allDays$Clicks / allDays$Impressions, 0)

#Removing age errors from the data
allDays <- subset(allDays, Age>0)

#Removing CTR errors from the data
#allDays <- subset(allDays, !is.na(CTR)) 

levels(allDays$whichDay) <- list(
                        'Day1' = 'Day1',
                        'Day2' = 'Day2',
                        'Day3' = 'Day3',
                        'Day4' = 'Day4',
                        'Day5' = 'Day5',
                        'Day6' = 'Day6',
                        'Day7' = 'Day7',
                        'Day8' = 'Day8',
                        'Day9' = 'Day9',
                        'Day10' = 'Day10'
                        )


allDays$age_category <- cut(
  allDays$Age,
  c(-Inf,0,29,39,49,59,Inf),
  labels = c("Invalid age","<30","30-39","40-49","50-50","60+")
)
#Plotting the distribution of number impressions and saving it to a .png file
png(file = "temp.png")
ggplot(data= allDays, aes(x=CTR, fill=Gender, color= Gender))+ geom_histogram(position = "dodge", binwidth=1)+ labs(title = "Comparison of CTR")+ facet_grid(.~ whichDay) 
dev.off()






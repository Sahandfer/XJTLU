library(doBy)
library(ggplot2)

# Read the data for 7 days
day1<-read.csv("Datasets/nyt1.csv")
day2<-read.csv("Datasets/nyt2.csv")
day3<-read.csv("Datasets/nyt3.csv")
day4<-read.csv("Datasets/nyt4.csv")
day5<-read.csv("Datasets/nyt5.csv")
day6<-read.csv("Datasets/nyt6.csv")
day7<-read.csv("Datasets/nyt7.csv")

# Adding a column to distinguish each day's data from others
day1$whichDay <- "Day1"
day2$whichDay <- "Day2"
day3$whichDay <- "Day3"
day4$whichDay <- "Day4"
day5$whichDay <- "Day5"
day6$whichDay <- "Day6"
day7$whichDay <- "Day7"

# Storing all the seven days' data into a single variable
allDays <- rbind(day1, day2, day3, day4, day5, day6, day7)

# Setting a level for each day
levels(allDays$whichDay) <- list(
  'Day1' = 'Day1',
  'Day2' = 'Day2',
  'Day3' = 'Day3',
  'Day4' = 'Day4',
  'Day5' = 'Day5',
  'Day6' = 'Day6',
  'Day7' = 'Day7'
)

# Setting the gender values to Male or Female (from 0 or 1)
allDays$Gender <- ifelse(allDays$Gender == 0, "M", "F")

# Assigning users to seven age categories (Excluding invalid)
allDays$ageCategory <- cut(
  allDays$Age,
  c(-Inf,0,17,24,34,44,54,64,Inf),
  labels = c("Invalid age","Under 18","18-24","25-34","35-44","45-54", "55-64", "65 and over")
)

# Calculating the Click-through-rate (CTR) for each user across all days
allDays$CTR <- ifelse(allDays$Impressions != 0, allDays$Clicks / allDays$Impressions, 0)

# Removing errors (Age is less than 3) and useless information (users who have not seen any ads; 0 impressions) from the data
# It is assumed that average children would have an understanding of simple software and internet tools by the age of 4
allDays <- subset(allDays, Age>3 & Impressions!=0)

# Defining the set of functions for obtaining required metrics
siterange <- function(x){c(length(x), min(x), max(x), mean(x))}

# Creating tables for number impressions based on gender, age groups and days respectively
impsTable_Age <-summaryBy(Impressions~ageCategory,data=allDays, FUN=siterange)
impsTable_Gender <-summaryBy(Impressions~Gender,data=allDays, FUN=siterange)
impsTable_Day <-summaryBy(Impressions~whichDay,data=allDays, FUN=siterange)

# Drawing the plot for number impressions based on gender, age groups and days
png(file = "Impressions.png")
ggplot(data = allDays, aes(x=Gender, y=Impressions, fill=whichDay, color= whichDay))+geom_bar(stat = "summary",fun.y="mean")+ labs(title = "Comparison of impressions during a week between differnet genders and age groups")+ facet_grid(.~ ageCategory)
dev.off()

# Creating a table for number of clicks based on gender, age groups and days respectively
clicksTable_Age <-summaryBy(Clicks~ageCategory,data=allDays, FUN=siterange)
clicksTable_Gender <-summaryBy(Clicks~Gender,data=allDays, FUN=siterange)
clicksTable_Day <-summaryBy(Clicks~whichDay,data=allDays, FUN=siterange)

# Drawing the plot for number of clicks based on gender, age groups and days
png(file = "Clicks.png")
ggplot(data = allDays, aes(x=Gender, y=Clicks, fill=whichDay, color= whichDay))+geom_bar(stat = "summary",fun.y="mean")+ labs(title = "Comparison of clicks during a week between differnet genders and age groups")+ facet_grid(.~ ageCategory)
dev.off()

# Creating a table for CTR based on gender, age groups and days respectively
ctrTable_Age <-summaryBy(CTR~ageCategory,data=allDays, FUN=siterange)
ctrTable_Gender <-summaryBy(CTR~Gender,data=allDays, FUN=siterange)
ctrTable_Day <-summaryBy(CTR~whichDay,data=allDays, FUN=siterange)

# Drawing the plot for CTR based on gender, age groups and days
png(file = "CTR.png")
ggplot(data = allDays, aes(x=Gender, y=CTR, fill=whichDay, color= whichDay))+geom_bar(stat = "summary",fun.y="mean")+ labs(title = "Comparison of CTR during a week between differnet genders and age groups")+ facet_grid(.~ ageCategory)
dev.off()


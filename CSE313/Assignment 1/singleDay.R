library(doBy)
library(ggplot2)

# Read the data for a single day
day1<-read.csv("Datasets/nyt1.csv")

#Grouping users to 5 age categories
day1$age_category <- cut(
  day1$Age,
  c(-Inf,0,29,39,49,59,Inf),
  labels = c("Invalid age","<30","30-39","40-49","50-50","60+")
)

#Setting the gender values to Male/Female (from 0 or 1)
day1$Gender <- ifelse(day1$Gender == 0, "Male", "Female")

#Calculating the Click-through-rate (CTR) for each user
day1$CTR <- ifelse(day1$Impressions != 0, day1$Clicks / day1$Impressions, 0)

#Removing age errors from the data
day1 <- subset(day1, age_category != "Invalid age")

#Plotting the distribution of number impressions and saving it to a .png file
png(file = "DistNumImps_SingleDay.png")
ggplot(data= day1, aes(x=Impressions, fill=age_category, color= age_category))+ geom_histogram(binwidth=1, position="dodge")+ labs(title = "Distribution of Number Impressions")
dev.off()

#Plotting the distribution of CTR and saving it to a .png file
png(file = "DistCTR_SingleDay.png")
ggplot(data= day1, aes(x=CTR, fill=age_category, color= age_category))+ geom_histogram(binwidth=0.1, position="dodge")+ labs(title = "Distribution of CTR")
dev.off()

#Grouping Genders to 2 age categories (<18 and 18+)
day1$age_category <- cut(
  day1$Age,
  c(-Inf,0,19,Inf),
  labels = c("Invalid age","<18","18+")
)

#Creating a table for number impressions based on gender and age groups
impsTable <-summaryBy(Impressions~Gender+age_category,data=day1, FUN=mean)

#Creating a table for numbe of clicks based on gender and age groups
clicksTable <-summaryBy(Clicks~Gender+age_category,data=day1, FUN=mean)

#Creating a table for CTR based on gender and age groups
ctrTable <-summaryBy(CTR~Gender+age_category,data=day1, FUN=mean)

#Plotting the CTR comparison between genders (with age groups) and saving it to a .png file
png(file = "CTRComparison_SingleDay.png")
ggplot(data= day1, aes(x=CTR, fill=Gender, color= Gender))+ geom_histogram(position = "dodge", binwidth=0.1)+ labs(title = "Comparison of CTR")+ facet_grid(.~ age_category) 
dev.off()

siterange <- function(x){c(length(x), min(x), max(x), mean(x))}
summaryBy(Age~agecat, data =data1, FUN=siterange)
summaryBy(Gender+Signed_In+Impressions+Clicks~agecat,data=data1)

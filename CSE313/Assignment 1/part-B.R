library(doBy)
library(plotrix)
library(ggplot2)

# Read the data for a single day or 10 days
day1<-read.csv("Datasets/nyt1.csv")
day1$age_category <- cut(
  day1$Age,
  c(-Inf,0,19,Inf),
  labels = c("Invalid age","<18","18+")
)

day1$Gender <- ifelse(day1$Gender == 0, 'Male', 'Female')

day1$scode[day1$Impressions==0] <- "NoImps"
day1$scode[day1$Impressions >0] <- "Imps"
day1$scode[day1$Clicks >0] <- "Clicks"

day1$scode <- factor(day1$scode) 

temp <- subset(day1, Age > 0 & age_category != "Invalid age")
clen <- function(x){c(length(x))}
impTable <-summaryBy(Impressions~Gender+age_category,data=temp, FUN=mean)
clickTable <-summaryBy(Clicks~Gender+age_category,data=temp, FUN=mean)

temp2 <- subset(temp, Impressions!= 0)
temp2$CTR <- temp2$Clicks / temp2$Impressions
ctrTable <-summaryBy(CTR~Gender+age_category,data=temp2, FUN=mean)

png(file = "comp.png")
ggplot(data= temp2, aes(x=CTR, fill=Gender, color= Gender))+ geom_histogram(position = "dodge", binwidth=0.1)+ labs(title = "Comparison of CTR")+ facet_grid(.~ age_category) 
dev.off()

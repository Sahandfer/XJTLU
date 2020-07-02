data1<-read.csv("Datasets/nyt1.csv")
library("doBy")
library(plotrix)
library(ggplot2)

#Find errors in data
amax <- max(data1$Age)
amin <- min(data1$Age)
print(amax)
print(amin)

#Finding number of wrong users
retval <- subset( data1, Age == 0)
print(nrow(retval))

#Grouping users
data1$agecat <- cut(data1$Age,c(-Inf, 0,18,24,34,44,54,64,Inf))
print(summary(data1$agecat))

#checking errors
print(summary(data1$Impressions))
print(summary(data1$Clicks))


#Using Siterange
siterange <- function(x){c(length(x), min(x), max(x), mean(x))}
summaryBy(Age~agecat, data =data1, FUN=siterange)
summaryBy(Gender+Signed_In+Impressions+Clicks~agecat,data=data1)



#############ACTUAL analysis##################
data1$hasimps <-cut(data1$Impressions,c(-Inf,0,Inf))
summaryBy(Impressions~hasimps, data =data1, FUN=siterange)
summaryBy(Clicks~hasimps, data=data1, FUN=siterange)

# create categories
data1$scode[data1$Impressions==0] <- "NoImps"
data1$scode[data1$Impressions >0] <- "Imps"
data1$scode[data1$Clicks >0] <- "Clicks"
# Convert the column to a factor
data1$scode <- factor(data1$scode)
head(data1)

clen <- function(x){c(length(x))}
etable <-summaryBy(Impressions~scode+Gender+agecat,data=data1, FUN=clen)
summaryBy(Impressions~scode+Gender+agecat,data=data1,FUN=clen)

ggplot(data1, aes(x=Impressions, fill=agecat))+ geom_histogram(binwidth=1)
ggplot(data1, aes(x=agecat, y=Impressions, fill=agecat)) + geom_boxplot()
ggplot(data1, aes(x=agecat, y=Clicks, fill=agecat)) + geom_boxplot()

data1$hasimps <-cut(data1$Impressions,c(-Inf,0,Inf))
summaryBy(Clicks~hasimps, data =data1, FUN=siterange)
ggplot(subset(data1, Impressions>0), aes(x=Clicks/Impressions,colour=agecat)) + geom_density()
ggplot(subset(data1, Clicks>0), aes(x=Clicks/Impressions,colour=agecat)) + geom_density()
ggplot(subset(data1, Clicks>0), aes(x=Clicks, colour=agecat))+ geom_density()




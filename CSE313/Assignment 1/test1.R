# Create a data frame.
data <- read.csv("input.csv")
print(data)

# Get the max salary from data frame.
sal <- max(data$salary)
print(sal)

# Get the person detail having max salary.
retval <- subset(data, salary == max(salary))
print(retval)

#Get all IT with salary> 600
retval <- subset( data, dept == "IT" & salary > 600 )
print(retval)

#Joined after 2014
retval <- subset(data, as.Date(start_date) > as.Date("2014-01-01"))
print(retval)


#Writing to CSV file
write.csv('',"output.csv", row.names = FALSE)
newdata <- read.csv("output.csv")
print(newdata)

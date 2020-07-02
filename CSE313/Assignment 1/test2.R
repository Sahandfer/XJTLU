# Create a vector. Using c - combination of elements
x <- c(12,7,3,4.2,18,2,54,-21,8,-5)
y <- c(12,7,3,4.2,NA,18,2,54,-21,8,-5, NA)

# Find Mean.
result.mean <- mean(x)
print(result.mean)

# Find Mean with 3 values from each side dropped.
result.mean <-  mean(x,trim = 0.3)
print(result.mean)

# Find Mean with missing values
result.mean <-  mean(y,na.rm = TRUE)
print(result.mean)

# Find the median.
median.result <- median(x)
print(median.result)


# Create the function.
getmode <- function(v) {
  uniqv <- unique(v)
  uniqv[which.max(tabulate(match(v, uniqv)))]
}

# Create the vector with numbers.
v <- c(2,1,2,3,1,2,3,4,1,5,5,3,2,3)

# Calculate the mode using the user function.
result <- getmode(v)
print(result)

# Create the vector with characters.
charv <- c("o","it","the","it","it")

# Calculate the mode using the user function.
result <- getmode(charv)
print(result)
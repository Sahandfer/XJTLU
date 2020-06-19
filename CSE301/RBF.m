%=========================================================================
% RBF for identifaction of car models
%=========================================================================
% PROBLEM DESCRIPTION:
% 5 classes of car logos are defined in a 80-dimensional input space.
% The task is to create an analyze an RBF network with different number of 
% centers and display the confusion matrix of the best model.
%=========================================================================
clear, close all, clc;
load('logo.mat')

%% Step 1. Define training and testing data
vehicle1=[]; % Labeled data for vehicle 1's logo
vehicle2=[]; % Labeled data for vehicle 2's logo
vehicle3=[]; % Labeled data for vehicle 3's logo
vehicle4=[]; % Labeled data for vehicle 4's logo
vehicle5=[]; % Labeled data for vehicle 5's logo

for i=1:length(eohsamples)
    switch(eohlabels(i))
        case(1)
            vehicle1 = [vehicle1;eohsamples(i, :), eohlabels(i)];
        case(2)
            vehicle2 = [vehicle2;eohsamples(i, :), eohlabels(i)];
        case(3)
            vehicle3 = [vehicle3;eohsamples(i, :), eohlabels(i)];
        case(4)
            vehicle4 = [vehicle4;eohsamples(i, :), eohlabels(i)];
        case(5)
            vehicle5 = [vehicle5;eohsamples(i, :), eohlabels(i)];
        otherwise
            disp('unknown label');
    end
end

% 80% of data for training
trainingData = [
    vehicle1(1:round(0.8*size(vehicle1, 1)), 1:80);
    vehicle2(1:round(0.8*size(vehicle2, 1)), 1:80);
    vehicle3(1:round(0.8*size(vehicle3, 1)), 1:80);
    vehicle4(1:round(0.8*size(vehicle4, 1)), 1:80);
    vehicle5(1:round(0.8*size(vehicle5, 1)), 1:80)
];
trainingLabels =[
    vehicle1(1:round(0.8*size(vehicle1, 1)), 81);
    vehicle2(1:round(0.8*size(vehicle2, 1)), 81);
    vehicle3(1:round(0.8*size(vehicle3, 1)), 81);
    vehicle4(1:round(0.8*size(vehicle4, 1)), 81);
    vehicle5(1:round(0.8*size(vehicle5, 1)), 81)
];

% 20% of data for testing
testingData = [
    vehicle1(round(0.8*size(vehicle1, 1): size(vehicle1, 1)), 1:80);
    vehicle2(round(0.8*size(vehicle2, 1): size(vehicle2, 1)), 1:80);
    vehicle3(round(0.8*size(vehicle3, 1): size(vehicle3, 1)), 1:80);
    vehicle4(round(0.8*size(vehicle4, 1): size(vehicle4, 1)), 1:80);
    vehicle5(round(0.8*size(vehicle5, 1): size(vehicle5, 1)), 1:80)
];
testingLabels = [
    vehicle1(round(0.8*size(vehicle1, 1): size(vehicle1, 1)), 81);
    vehicle2(round(0.8*size(vehicle2, 1): size(vehicle2, 1)), 81);
    vehicle3(round(0.8*size(vehicle3, 1): size(vehicle3, 1)), 81);
    vehicle4(round(0.8*size(vehicle4, 1): size(vehicle4, 1)), 81);
    vehicle5(round(0.8*size(vehicle5, 1): size(vehicle5, 1)), 81)
];

%% Step 2
Inputs = trainingData'; % The training inputs
Outputs = trainingLabels'; % The training targets
Inputs_T = testingData'; % The testing inputs
Outputs_T= testingLabels'; % The testing targets

MSE = [];

for numCenter=1:1:50 % number of RBF centers
    % Find the centers using k-means
    [idx, centers] = kmeans(trainingData, numCenter);

    % Training the RBF network
    phi = zeros(length(trainingData), numCenter);
    for N=1:length(trainingData) % each training sample
        for n=1:numCenter % for each hidden neuron
            dist = norm(trainingData(N, :)-centers(n, :));
            variance = 1;
            phi(N, n) = exp((-1*(dist)^2)/2*variance);
        end
    end
    phiPlus = pinv(phi); %psuedo-inverse of phi
    W = phiPlus*trainingLabels; % the weight vector


    output = zeros(size(testingData, 1), 1);
    % Testing the RBF network
    for N=1:size(testingData, 1) % each training sample
        sum = 0;
        for n=1:numCenter % for each hidden neuron
            dist = norm(centers(n, :)-testingData(N, :));
            variance = 1;
            phi_test = exp((-1*(dist)^2)/2*variance);
            sum = sum+ (W(n)*phi_test);
        end
        output(N) = sum;
    end
    
    MSE(numCenter)= immse(output, testingLabels);
end

[minMSE, numCenter] = min(MSE);
figure(1);
plot(1:1:50, MSE)
title('MSE comparison for different RBF centers')
xlabel('Number of RBF centers')
ylabel('Mean Squared Error (MSE)')
xlim([0, 50])

% Find the centers using k-means
[idx, centers] = kmeans(trainingData, numCenter);

% Training the RBF network
phi = zeros(length(trainingData), numCenter);
for N=1:length(trainingData) % each training sample
    for n=1:numCenter % for each hidden neuron
        dist = norm(trainingData(N, :)-centers(n, :));
        variance = 1;
        phi(N, n) = exp((-1*(dist)^2)/2*variance);
    end
end
phiPlus = pinv(phi); %psuedo-inverse of phi
W = phiPlus*trainingLabels; % the weight vector


output = zeros(size(testingData, 1), 1);
% Testing the RBF network
for N=1:size(testingData, 1) % each training sample
    sum = 0;
    for n=1:numCenter % for each hidden neuron
        dist = norm(centers(n, :)-testingData(N, :));
        variance = 1;
        phi_test = exp((-1*(dist)^2)/2*variance);
        sum = sum+ (W(n)*phi_test);
    end
    output(N) = sum;
end

% Drawing the confusion matrix [1] for the best RBF model
targets = zeros(5,length(testingLabels'));
outputs = zeros(5,length(output'));
target_indexes = sub2ind(size(targets), testingLabels', 1:length(testingLabels'));
output_indexes = sub2ind(size(outputs), round(output'), 1:length(output'));
targets(target_indexes) = 1;
outputs(output_indexes) = 1;
figure(2);
plotconfusion(targets,outputs)

%=========================================================================
% References:
% [1] MathWorks Support Team, (2017, Jul. 5) How can I plot a confusion 
% matrix for a multi-class or non-binary classification problem?,[Online].
% Available: https://www.mathworks.com/matlabcentral/answers/338244-how-can
% -i-plot-a-confusion-matrix-for-a-multi-class-or-non-binary-classification
% -problem
%=========================================================================





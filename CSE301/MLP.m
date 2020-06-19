%=========================================================================
% MLP using backpropagation for identifaction of car models
%=========================================================================
% PROBLEM DESCRIPTION:
% 5 classes of car logos are defined in a 80-dimensional input space.
% The task is to create an analyze an MLP network with different parameters
% and display the confusion matrix of the best model.
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
%% Step 2 Create, train, and test MLP for different parameters
learningRate= 0.1; % the learning rate
momentum=0.1; % momentum
numHidden =10; % number of units in the hidden layer 
epochs=100; % number of epochs

Inputs = trainingData'; % The training inputs
Outputs = trainingLabels'; % The training targets
Inputs_T = testingData'; % The testing inputs
Outputs_T= testingLabels'; % The testing targets

MSE = []; % vector of MSE for different values of same parameter

% Testing the network for different number of hidden units
for i=1:1:10
    MSE(i) = MLPnetwork(Inputs,Outputs, Inputs_T, Outputs_T, i, learningRate, momentum, epochs); % Calculate MSE
end

[minMSE, numHidden]= min(MSE); % The best model's num of units for hidden layer
figure(1);
plot(1:1:10, MSE)
title('MSE comparison for different number of units in hidden layer')
xlabel('Units in hidden layer')
ylabel('Mean Squared Error (MSE)')
grid on

idx= 1;
% Testing the network for different learning rate
for i=0:0.1:1
    MSE(idx) = MLPnetwork(Inputs,Outputs, Inputs_T, Outputs_T, numHidden, i, momentum, epochs); % Calculate MSE
    idx = idx+1;
end

[minMSE, idx]= min(MSE); % The best model's learning rate
learningRate = idx/10;
figure(2);
plot(0:0.1:1, MSE)
title('MSE comparison for different learning rates')
xlabel('Learning Rate')
ylabel('Mean Squared Error (MSE)')
grid on

idx= 1;
% Testing the network for momentum
for i=0:0.1:1
    MSE(idx) = MLPnetwork(Inputs,Outputs, Inputs_T, Outputs_T, numHidden, learningRate, i, epochs); % Calculate MSE
    idx = idx+1;
end

[minMSE, idx]= min(MSE); % The best model's learning rate
momentum = idx/10;
figure(3);
plot(0:0.1:1, MSE)
title('MSE comparison for different momentum')
xlabel('Momentum')
ylabel('Mean Squared Error (MSE)')
grid on


% Creating the best MLP model
[msError, Y, Y1] = MLPnetwork(Inputs,Outputs, Inputs_T, Outputs_T, numHidden, learningRate, momentum, epochs);
targets = zeros(5,length(Outputs_T));
outputs = zeros(5,length(Y1));
targetsIdx = sub2ind(size(targets), Outputs_T, 1:length(Outputs_T));
outputsIdx = sub2ind(size(outputs), round(Y1), 1:length(Y1));
targets(targetsIdx) = 1;
outputs(outputsIdx) = 1;
figure(4);
plotconfusion(targets,outputs)
grid on


% Function for creating a MLP network with given parameters
% This returns the testing and training outputs as well as the MSE
function[msError, Y, Y1] = MLPnetwork(I, O, I_T, O_T, NH, LR, MC, E)
    net = newff(I, O, NH, {'logsig', 'tansig'}, 'traingdm');
    net= setwb(net, zeros(1, net.numWeightElements)); % set initial weights to 0
    net.trainParam.epochs = E; % set the maximum number of epochs
    net.trainParam.lr = LR; % set the learning rate
    net.trainParam.mc = MC; % set the momentum
    net.divideParam.trainRatio = 1; % all of testing data is used for training
    net.divideParam.testRatio = 0;% no data for testing
    net.divideParam.valRatio = 0; % no data for validation

    [net,tr,Y] = train(net,I,O); % Train the network

    Y1 = sim(net, I_T); % Test the network
    msError = mse(net, O_T, Y1); % Calculate MSE
end

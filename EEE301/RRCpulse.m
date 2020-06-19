clear, close all, clc;

% Setting the system paramters
sampleRate = 8; % the sample rate
bitRate = 1; % the bit rate
rollOff = 1; % roll-off factor
symbolNum = 4096; % number of symbols
sampleNum = 8; % number of samples per symbol
M = symbolNum*sampleNum; % number of sample columns
N = 1; % number of sample rows
signalRange = [0 1]; % Range for the random signal 
sampleRateOD = 1; % used for over/down sampling
span=8; %used for the truncating window

inc = bitRate/sampleRate;%The time increment
total = symbolNum*sampleNum*inc;% total data

T = 8; % signal period
t = 0:inc:total-inc; % data transmission time

% Creating the signal source
uniSrc = randi(signalRange, M, N); % Unipolar signal (0 or 1)
biSrc = 2*randi(signalRange,M, N)-1; % Bipolar signal (-1 or 1)

% Drawing the unipolar signal source
figure;
plot(t, uniSrc);
title('Unipolar signal source'); 
grid on;
axis([0 8 -0.5 1.5]);
% Drawing the bipolar signal source
figure;
plot(t, biSrc);
title('Bipolar signal source'); 
grid on;
axis([0 8 -1.5 1.5]);

% RRC Pulse Shaping
coeffs = rcosdesign(rollOff, span, sampleNum, 'sqrt'); % RRC coefficients
rrcPulseUni = upfirdn(uniSrc, coeffs, sampleNum); % Oversampled and RCC shaped Unipolar signal
rrcPulseBi = upfirdn(biSrc, coeffs, sampleNum); % Oversampled and RCC shaped Bipolar signal

% Drawing the unipolar signal source (pulse-shaped)
t1 = 0:1:size(rrcPulseUni, 1)-1; 
figure;
plot(t1, rrcPulseUni);
title('Unipolar rrc-pulse-shaped signal'); 
grid on;
axis([0 1024 -0.2 0.5]);

% Drawing the unipolar signal source (pulse-shaped)
figure;
plot(t1, rrcPulseBi);
title('Bipolar rrc-pulse-shaped signal'); 
grid on;
axis([0 1024 -0.6 0.6]);

% Plot the baseband with arbitary noise power
noiseRRCUni = awgn(rrcPulseUni, 20, 'measured'); % add noise to signal
figure;
plot(t1, rrcPulseUni);
hold on
plot(t1, noiseRRCUni);
hold off
title('Unipolar RRC-pulse-shaped signal with noise (baseband signal)'); 
xlabel('Time');
ylabel('Magnitude');
grid on;
legend('Pulse-shaped signal','Pulse-shaped signal with noise');
axis([0 1024 -0.2 0.5]);
% plot the bipolar baseband
noiseRRCBi = awgn(rrcPulseBi, 20, 'measured');
figure;
plot(t1, rrcPulseBi);
hold on
plot(t1, noiseRRCBi);
hold off
title('Bipolar RRC-pulse-shaped signal with noise (baseband signal)'); 
xlabel('Time');
ylabel('Magnitude');
grid on;
legend('Pulse-shaped signal','Pulse-shaped signal with noise');
axis([0 1024 -0.6 0.6]);

PSDW = 4096; % the PSD window size
%Plotting PSD for unipolar signaling
figure;
[pxx, freq] = pwelch(noiseRRCUni, PSDW, PSDW/2, 'centered', 'power');
power = 10*log10(pxx);
plot(freq, power);
title('PSD of Uniploar rrc-pulse-shaped signal'); 
xlabel('Frequency (Hz)');
ylabel('Magnitude (dB)');
grid on;
%Plotting PSD for bipolar signaling
figure;
[pxx, freq] = pwelch(noiseRRCBi, PSDW, PSDW/2, 'centered', 'power');
power = 10*log10(pxx);
plot(freq, power);
title('PSD of Biploar rrc-pulse-shaped signal'); 
xlabel('Frequency (Hz)');
ylabel('Magnitude (dB)');
grid on;

% Applying channel model
N0 = -40:1:40 %arbitrary channel power
BER_Uni= zeros(length(N0), 1); %list of BER for unipolar
BER_Bi= zeros(length(N0), 1); %list of BER for bipolar
index = 1;%indicates the BER index
for N0 = -40:1:40
    SNR= N0- 10*log10(8); %calculate SNR
    noiseRRCUni = awgn(rrcPulseUni, SNR, 'measured');%add noise
    noiseRRCBi = awgn(rrcPulseBi, SNR, 'measured');%add noise
    
    % Matched Filter and downsample for unipolar
    rcvSignal = upfirdn(noiseRRCUni, coeffs, 1, sampleNum);
    % Removing filter delay for unipolar
    rcvUni = rcvSignal((sampleNum)+1:end-(sampleNum));
    % Matched Filter and downsample for bipolar
    rcvSignal = upfirdn(noiseRRCBi, coeffs, 1, sampleNum);
    % Removing filter delay for bipolar
    rcvBi = rcvSignal((sampleNum)+1:end-(sampleNum));

    % Pulse detection for unipolar
    resultUni= []; % the results of pulse detection
    for i=1:length(rcvUni)
        if (rcvUni(i)>0.4) %compare to threshold
            resultUni(i) = 1;
        else
            resultUni(i) = 0;
        end
    end
    
    % Pulse detection and down sampling for unipolar
    resultBi= []; % the results of pulse detection
    for i=1:length(rcvBi)
        if (rcvBi(i)>0) %compare to threshold
            resultBi(i) = 1;
        else
            resultBi(i) = -1;
        end
    end
    
    errorNum = 0; %number of errors
    for i=1:length(uniSrc)
        if (uniSrc(i)~=resultUni(i)) %if bit error
            errorNum= errorNum+1;
        end
    end
    %calculate BER
    BER_Uni(index)= errorNum/length(uniSrc);
    
    errorNum = 0; %number of errors
    for i=1:length(biSrc)
        if (biSrc(i)~=resultBi(1, i)) %if bit error
            errorNum= errorNum+1;
        end
    end
    %calculate BER
    BER_Bi(index)= errorNum/length(biSrc);
    %increment index for next loop
    index = index+1;
end

N0 = -40:1:40; %arbitrary noise power
EbN0 = 0.0625./(10.^(N0./10)); %SNR for unipolar
tBER=qfunc(sqrt(EbN0)); %Theoretical BER for unipolar
figure;
%Draw the analytical BER vs Eb/No
semilogy(N0,(BER_Uni));
hold on 

semilogy(10*log10(2*EbN0),(tBER));
hold off
title('BER performance for unipolar RRC pulse shaping');
legend('Analytical BER vs Eb/No','Theoretical BER vs Eb/No');
xlabel('Eb/No (dB)');
ylabel('BER');
grid on;
axis([-5 15 0.001 0.5]);

N0 = -40:1:40; %arbitrary noise power
EbN0 = 0.25./(10.^(N0./10));%SNR for bipolar
tBER=qfunc(sqrt(EbN0)); %Theoretical BER for bipolar
figure;
%Draw the analytical BER vs Eb/No
semilogy(N0,(BER_Bi));
hold on 
%Draw the theoretical BER vs Eb/No
semilogy(10*log10(EbN0),(tBER));
hold off
title('BER performance for bipolar RRC pulse shaping');
legend('Analytical BER vs Eb/No','Theoretical BER vs Eb/No');
xlabel('Eb/No (/dB)');
ylabel('BER');
grid on;
axis([-5 15 0.001 0.5]);


N0 = -40:1:40; %arbitrary noise power
figure;
%Plot BER for bipolar
semilogy(N0,(BER_Bi));
hold on 
%Plot BER for unipolar
semilogy(N0,(BER_Uni));
hold off
title('BER comparison for RRC pulse shaping');
legend('Bipolar','Unipolar')
xlabel('Eb/No (/dB)');
ylabel('Bit Error Rate ');
grid on;
axis([-5 15 0.001 0.5]);
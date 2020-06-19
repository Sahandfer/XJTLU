clear, close all, clc;

% Setting the system paramters
sampleRate = 8; % the sample rate
bitRate = 1; % the bit rate
symbolNum = 4096; % number of symbols
sampleNum = 8; % number of samples per symbol
M = symbolNum*sampleNum; % number of sample columns
N = 1; % number of sample rows
signalRange = [0 1]; % Range for the random signal 
sampleRateOD = 1; % used for over/down sampling

inc = bitRate/sampleRate; %The time increment
total = symbolNum*sampleNum*inc; % total data

T = 8; % signal period
t = 0:inc:total-inc; % data transmission time

% Creating the signal source
uniSrc = randi(signalRange, M, N); % Unipolar signal (0 or 1)
biSrc = 2*randi(signalRange,M, N)-1; % Bipolar signal (-1 or 1)
% Drawing the unipolar signal source
figure;
plot(t, uniSrc);
title('Unipolar signal source'); 
xlabel('Time');
ylabel('Magnitude');
grid on;
axis([0 8 -0.5 1.5]);
% Drawing the bipolar signal source
figure;
plot(t, biSrc);
title('Bipolar signal source'); 
xlabel('Time');
ylabel('Magnitude');
grid on;
axis([0 8 -1.5 1.5]);

% Rectangular Pulse Shaping
rectPulseUni = rectpulse(uniSrc, sampleNum); %unipolar
rectPulseBi = rectpulse(biSrc, sampleNum);%bipolar

% Drawing the unipolar signal source (pulse-shaped)
t1 = 0:inc:sampleNum*total-inc; 
figure;
plot(t1, rectPulseUni);
title('Unipolar rect-pulse-shaped signal'); 
xlabel('Time');
ylabel('Magnitude');
grid on;
axis([0 64 -0.5 1.5]);

% Drawing the bipolar signal source (pulse-shaped)
figure;
plot(t1, rectPulseBi);
title('Bipolar rect-pulse-shaped signal'); 
xlabel('Time');
ylabel('Magnitude');
grid on;
axis([0 64 -1.5 1.5]);

% Plot the baseband with arbitary noise power
noiseRectUni = awgn(rectPulseUni, 20, 'measured'); %add noise
figure;
plot(t1, rectPulseUni);
hold on
plot(t1, noiseRectUni);
hold off
title('Unipolar rect-pulse-shaped signal with noise (baseband signal)'); 
xlabel('Time');
ylabel('Magnitude');
grid on;
legend('Pulse-shaped signal','Pulse-shaped signal with noise');
axis([0 64 -0.5 1.5]);
% plot the bipolar baseband
noiseRectBi = awgn(rectPulseBi, 20, 'measured'); %add noise
figure;
plot(t1, rectPulseBi);
hold on
plot(t1, noiseRectBi);
hold off
title('Bipolar rect-pulse-shaped signal with noise (baseband signal)'); 
xlabel('Time');
ylabel('Magnitude');
grid on;
legend('Pulse-shaped signal','Pulse-shaped signal with noise');
axis([0 64 -1.5 1.5]);

PSDW = 4096; % the PSD window size
%Plotting PSD for unipolar signaling
figure;
[pxx, freq] = pwelch(noiseRectUni, PSDW, PSDW/2, 'centered', 'power');
power = 10*log10(pxx);
plot(freq, power);
title('PSD of Uniploar baseband signal (rect-pulse-shaped)'); 
xlabel('Frequency (Hz)');
ylabel('Magnitude (dB)');
grid on;
%Plotting PSD for bipolar signaling
figure;
[pxx, freq] = pwelch(noiseRectBi, PSDW, PSDW/2, 'centered', 'power');
power = 10*log10(pxx);
plot(freq, power);
title('PSD of Biploar baseband signal (rect-pulse-shaped)'); 
xlabel('Frequency (Hz)');
ylabel('Magnitude (dB)');
grid on;

% Applying channel model
N0 = -10:1:10; %arbitrary channel power
BER_Uni= zeros(length(N0), 1); %list of BER for unipolar
BER_Bi= zeros(length(N0), 1); %list of BER for bipolar
index = 1;%indicates the BER index
for N0 = -10:1:10
    noiseRectUni = awgn(rectPulseUni, N0, 'measured');%add noise
    noiseRectBi = awgn(rectPulseBi, N0, 'measured');%add noise
    
    % Matched Filter
    HF=ones(sampleRate, 1);
    % Matched Filtering for unipolar
    rcvSignal = conv(noiseRectUni, HF).';
    % circular shifting
    rcvSignal= circshift(rcvSignal,[0, -7]);
    %down sampling
    rcvUni = downsample(rcvSignal, sampleNum);
    % Matched Filtering for bipolar
    rcvSignal = conv(noiseRectBi, HF).';
    % circular shifting
    rcvSignal= circshift(rcvSignal,[0, -7]);
    %down sampling
    rcvBi = downsample(rcvSignal, sampleNum);

    % Pulse detection for unipolar
    resultUni= [];% the results of pulse detection
    for i=1:length(rcvUni)
        if (rcvUni(i)>4) %compare to threshold
            resultUni(i) = 1;
        else
            resultUni(i) = 0;
        end
    end
    % Pulse detection for bipolar
    resultBi= [];% the results of pulse detection
    for i=1:length(rcvBi)
        if (rcvBi(i)>0) %compare to threshold
            resultBi(i) = 1;
        else
            resultBi(i) = -1;
        end
    end
    
    errorNum = 0; %number of errors
    for i=1:length(uniSrc)
        if (uniSrc(i)~=resultUni(i))%if bit error
            errorNum= errorNum+1;
        end
    end
    %calculate BER
    BER_Uni(index)= errorNum/length(uniSrc);
    
    errorNum = 0;%number of errors
    for i=1:length(biSrc)
        if (biSrc(i)~=resultBi(i))%if bit error
            errorNum= errorNum+1;
        end
    end
    %calculate BER
    BER_Bi(index)= errorNum/length(biSrc);
    %increment index for next loop
    index = index+1;
end

N0 = -10:1:10;%arbitrary noise power
EbN0 = 8./(10.^(N0./10)); %SNR for unipolar
tBER=qfunc(sqrt(EbN0)); %Theoretical BER for unipolar
B = 2/T; %bandwidth
figure;
%Draw the analytical BER vs Eb/No
semilogy(N0,(BER_Uni));
hold on
%Draw the theoretical BER vs Eb/No
semilogy(10*log10(B.*EbN0),(tBER));
hold off
title('BER performance for unipolar rectangular pulse shaping');
legend('Analytical BER vs Eb/No','Theoretical BER vs Eb/No');
xlabel('Eb/No (dB)');
ylabel('BER');
grid on;
axis([-5 5 0.001 0.5]);

figure;
N0 = -10:1:10;%arbitrary noise power
EbN0 = 8./(10.^(N0./10));%Theoretical BER for unipolar
B = 2/T;%bandwidth
tBER=qfunc(sqrt(2*EbN0)); %Theoretical BER for unipolar
%Draw the analytical BER vs Eb/No
semilogy(N0,(BER_Bi));
hold on
%Draw the theoretical BER vs Eb/No
semilogy(10*log10(B.*EbN0),(tBER));
hold off
title('BER performance for bipolar rectangular pulse shaping');
legend('Analytical BER vs Eb/No','Theoretical BER vs Eb/No');
xlabel('Eb/No (/dB)');
ylabel('BER');
grid on;
axis([-5 5 0.001 0.5]);

figure;
%Plot BER for bipolar
semilogy(N0,(BER_Bi));
hold on 
%Plot BER for unipolar
semilogy(N0,(BER_Uni));
hold off
title('BER comparison for rectangular pulse shaping');
legend('Bipolar','Unipolar');
xlabel('Eb/No (/dB)');
ylabel('Bit Error Rate ');
grid on;
axis([-5 5 0.001 0.5]);
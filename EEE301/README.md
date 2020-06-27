# Lab Assignment 
## Introduction

In this Lab assignment, you will use MATLAB to develop a baseband transceiver for binary digital signals, including verification of BER performance of the optimum receiver (i.e., matched filter of shaped pulses).

## Procedure

1) Set system parameters– Including data rate, bit rate, signal (i.e., bipolar vs. unipolar binary sequence), pulse shaping (i.e., rectangular vs. root raised cosine (RRC)), number of samples per bit, pulse roll-off factor
and so on.

2) Create a binary sequence as a signal source.
3) Perform pulse shaping:
	3.1) Oversampling.
	3.2) Rectangular or RRC pulse shaping.
4) Apply channel model (AWGN).
5) Perform pulse detection (matched filtering) and down-sample the signal.
	5.1) Matched filtering.
	5.2) Downsampling.
6) Compute and plot BER vs. Eb=N0.
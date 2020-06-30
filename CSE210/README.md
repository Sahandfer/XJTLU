# Coursework

The objective of the coursework is to develop a practical application for data processing, analysis and content search based on the object-oriented principles you learn from the CSE210 module. 

## Content Search

Effective tweet searching is an important functionality for users, especially when there are millions of tweets published in each single day. The search process takes a user’s input keyword as a query and then retrieves relevant tweets. Two simple searching strategies are considered.

1. Text matching – The idea is to find tweets based on matching the user’s keyword (only one word) with all the tweets. A tweet is regarded as relevant if the keyword appears in it. This is a basic feature of the application.

2. Full text search – This is considered as an advanced feature of the application. To simplify the problem, you do NOT need to study the techniques in the field of Information Retrieval. According to the research reported in [1], the full text search functionality on Twitter is based on a modified version of the Apache Lucene API. However, the actual full text search on Twitter is extremely complicated. This coursework only attempts to build a much simpler full text search engine based on the original Lucene API, only for limited amount of Twitter data. Lucene can be downloaded at: https://lucene.apache.org/core/. A tutorial is available here: https://lucene.apache.org/core/7_7_1/demo/overview-summary.html
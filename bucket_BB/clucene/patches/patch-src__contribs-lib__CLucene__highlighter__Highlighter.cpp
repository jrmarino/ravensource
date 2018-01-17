--- src/contribs-lib/CLucene/highlighter/Highlighter.cpp.orig	2011-03-17 00:21:07 UTC
+++ src/contribs-lib/CLucene/highlighter/Highlighter.cpp
@@ -214,8 +214,9 @@ CL_NS_USE(util)
 			int32_t startOffset;
 			int32_t endOffset;
 			int32_t lastEndOffset = 0;
+			int len;
 			_textFragmenter->start(text);
-			TCHAR substringBuffer[LUCENE_MAX_WORD_LEN];
+			TCHAR substringBuffer[LUCENE_MAX_WORD_LEN+1];
 
 			TokenGroup* tokenGroup=_CLNEW TokenGroup();
 
@@ -229,8 +230,9 @@ CL_NS_USE(util)
 					 startOffset = tokenGroup->getStartOffset();
 					 endOffset = tokenGroup->getEndOffset();
 
-					 _tcsncpy(substringBuffer,text+startOffset,endOffset-startOffset);
-					 substringBuffer[endOffset-startOffset]=_T('\0');
+					 len = cl_min(endOffset-startOffset,LUCENE_MAX_WORD_LEN);
+					 _tcsncpy(substringBuffer,text+startOffset,len);
+					 substringBuffer[len]=_T('\0');
 
 					 TCHAR* encoded = _encoder->encodeText(substringBuffer);
 					 TCHAR* markedUpText=_formatter->highlightTerm(encoded, tokenGroup);
@@ -238,9 +240,7 @@ CL_NS_USE(util)
 
 					 //store any whitespace etc from between this and last group
 					 if (startOffset > lastEndOffset){
-						 int len = startOffset-lastEndOffset;
-						 if ( len > LUCENE_MAX_FIELD_LEN )
-							 len = LUCENE_MAX_FIELD_LEN;
+						 len = cl_min(startOffset-lastEndOffset,LUCENE_MAX_FIELD_LEN);
 						 _tcsncpy(buffer,text+lastEndOffset,len);
 						 buffer[len]=_T('\0');
 
@@ -287,8 +287,9 @@ CL_NS_USE(util)
   	            startOffset = tokenGroup->getStartOffset();
   	            endOffset = tokenGroup->getEndOffset();
 
-				_tcsncpy(substringBuffer,text+startOffset,endOffset-startOffset);
-				substringBuffer[endOffset-startOffset]=_T('\0');
+		    len = cl_min(endOffset-startOffset,LUCENE_MAX_WORD_LEN);
+		    _tcsncpy(substringBuffer,text+startOffset,len);
+		    substringBuffer[len]=_T('\0');
 
 				TCHAR* encoded = _encoder->encodeText(substringBuffer);
         TCHAR* markedUpText=_formatter->highlightTerm(encoded, tokenGroup);
@@ -393,6 +394,7 @@ CL_NS_USE(util)
 				}
 			}
 		)
+		return NULL;
 	}
 
 

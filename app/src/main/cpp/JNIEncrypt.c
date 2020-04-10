#include <jni.h>
#include "aes.h"
#include <string.h>

#define CBC 1
#define ECB 1


// 获取数组的大小
# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
// 指定要注册的类，对应完整的java类名
#define JNIREG_CLASS "com/sh/sdk/shareinstall/business/jni/AESEncrypt"


jstring charToJstring(JNIEnv *envPtr, char *src) {
	JNIEnv env = *envPtr;

	jsize len = strlen(src);
	jclass clsstring = env->FindClass(envPtr, "java/lang/String");
	jstring strencode = env->NewStringUTF(envPtr, "UTF-8");
	jmethodID mid = env->GetMethodID(envPtr, clsstring, "<init>",
	                                 "([BLjava/lang/String;)V");
	jbyteArray barr = env->NewByteArray(envPtr, len);
	env->SetByteArrayRegion(envPtr, barr, 0, len, (jbyte *) src);

	return (jstring) env->NewObject(envPtr, clsstring, mid, barr, strencode);
}

//__attribute__((section (".mytext")))//隐藏字符表 并没有什么卵用 只是针对初阶hacker的一个小方案而已
char *getKey() {
	int n = 0;
	char s[23];//"NMTIzNDU2Nzg5MGFiY2RlZg"; 原字符串：1234567890abcdef base64编码后 MTIzNDU2Nzg5MGFiY2RlZg==  去掉后面的两个==，首位加上N

	s[n++] = 'N';
	s[n++] = 'M';
	s[n++] = 'T';
	s[n++] = 'I';
	s[n++] = 'z';
	s[n++] = 'N';
	s[n++] = 'D';
	s[n++] = 'U';
	s[n++] = '2';
	s[n++] = 'N';
	s[n++] = 'z';
	s[n++] = 'g';
	s[n++] = '5';
	s[n++] = 'M';
	s[n++] = 'G';
	s[n++] = 'F';
	s[n++] = 'i';
	s[n++] = 'Y';
	s[n++] = '2';
	s[n++] = 'R';
	s[n++] = 'l';
	s[n++] = 'Z';
	s[n++] = 'g';

	char *encode_str = s + 1;
	return b64_decode(encode_str, strlen(encode_str));

}

JNIEXPORT jstring JNICALL encode(JNIEnv *env, jobject instance, jstring str_) {

	uint8_t *AES_KEY = (uint8_t *) getKey();
	const char *in = (*env)->GetStringUTFChars(env, str_, JNI_FALSE);
	char *baseResult = AES_128_ECB_PKCS5Padding_Encrypt(in, AES_KEY);
	(*env)->ReleaseStringUTFChars(env, str_, in);
	jstring result = (*env)->NewStringUTF(env, baseResult);
	free(baseResult);
	free(AES_KEY);
	return result;
}


JNIEXPORT jstring JNICALL decode(JNIEnv *env, jobject instance, jstring str_) {

	uint8_t *AES_KEY = (uint8_t *) getKey();
	const char *str = (*env)->GetStringUTFChars(env, str_, JNI_FALSE);
	char *desResult = AES_128_ECB_PKCS5Padding_Decrypt(str, AES_KEY);
	(*env)->ReleaseStringUTFChars(env, str_, str);
//    return (*env)->NewStringUTF(env, desResult);
	//不用系统自带的方法NewStringUTF是因为如果desResult是乱码,会抛出异常
//    return charToJstring(env,desResult);
	jstring result = charToJstring(env, desResult);
	free(desResult);
	free(AES_KEY);
	return result;
}


// Java和JNI函数的绑定表
static JNINativeMethod method_table[] = {
		{"encode", "(Ljava/lang/String;)Ljava/lang/String;", (void *) encode},
		{"decode", "(Ljava/lang/String;)Ljava/lang/String;", (void *) decode}
};

// 注册native方法到java中
static int registerNativeMethods(JNIEnv *env, const char *className,
                                 JNINativeMethod *gMethods, int numMethods) {
	jclass clazz;
	clazz = (*env)->FindClass(env, className);
	if (clazz == NULL) {
		return JNI_FALSE;
	}
	if ((*env)->RegisterNatives(env, clazz, gMethods, numMethods) < 0) {
		return JNI_FALSE;
	}

	return JNI_TRUE;
}

int register_ndk_load(JNIEnv *env) {
	// 调用注册方法
	return registerNativeMethods(env, JNIREG_CLASS,
	                             method_table, NELEM(method_table));
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {

	JNIEnv *env = NULL;
	jint result = -1;

	if ((*vm)->GetEnv(vm, (void **) &env, JNI_VERSION_1_4) != JNI_OK) {
		return result;
	}

	register_ndk_load(env);

// 返回jni的版本
	return JNI_VERSION_1_4;
}


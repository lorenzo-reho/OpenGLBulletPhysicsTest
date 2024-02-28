#include "GBuffer.h"

void GBuffer::Init() {
	

	glGenFramebuffers(1, &_gBuffer);
	// glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);

	// Ogni "pixel" del framebuffer contiene 3 informazioni
	// Una per ognuna delle seguenti texture
	Configure();


}

void GBuffer::Configure() {
	glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);

	// Fragment position texture --> High Precision texture 16bit
	glGenTextures(1, &_gPosition);
	glBindTexture(GL_TEXTURE_2D, _gPosition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, GL::GetWindowWidth(), GL::GetWindowHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Il position buffer ha indice 0... quindi quando vorremo accedere
	// a questa texture potremo farlo tramite layout location=0
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _gPosition, 0);

	// Normal texture
	glGenTextures(1, &_gNormal);
	glBindTexture(GL_TEXTURE_2D, _gNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, GL::GetWindowWidth(), GL::GetWindowHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _gNormal, 0);


	glGenTextures(1, &_gAlbedoSpec);
	glBindTexture(GL_TEXTURE_2D, _gAlbedoSpec);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GL::GetWindowWidth(), GL::GetWindowHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, _gAlbedoSpec, 0);

	// diciamo ad opengl quali GL_COLOR_ATTACHMENTX utilizzeremo per il rendering
	unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);

	glGenRenderbuffers(1, &_gDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, _gDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, GL::GetWindowWidth(), GL::GetWindowHeight());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _gDepth);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);



}


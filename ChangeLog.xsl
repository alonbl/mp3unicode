<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text"/>
<xsl:variable name="text_width" select="65"/>

<xsl:template match="/">
  <xsl:text>mp3unicode ChangeLog&#xA;&#xA;</xsl:text>
  <xsl:apply-templates select="releases/release"/>
</xsl:template>

<xsl:template match="release">
  <xsl:value-of select="date"/>
  <xsl:text> -- Version </xsl:text>
  <xsl:value-of select="version"/>
  <xsl:text>&#xA;</xsl:text>
  <xsl:apply-templates select="changes/change"/>
  <xsl:if test="position() != last()">
    <xsl:text>&#xA;&#xA;</xsl:text>
  </xsl:if>
</xsl:template>

<xsl:template match="change">
  <xsl:apply-templates/>
  <xsl:text>&#xA;</xsl:text>
</xsl:template>

<xsl:template match="text()">
  <xsl:text>*</xsl:text>
  <xsl:call-template name="wrapper">
    <xsl:with-param name="offset" select="1"/>
    <xsl:with-param name="width" select="0"/>
  </xsl:call-template>
</xsl:template>

<xsl:template name="wrapper">
  <xsl:param name="offset"/>
  <xsl:param name="width"/>
  <xsl:variable name="token" select="substring-before(substring(concat(.,' '),$offset),' ')"/>
  <xsl:if test="string-length($token)>0">
    <xsl:if test="$text_width>=string-length($token)+$width+1">
      <xsl:text> </xsl:text><xsl:value-of select="$token"/>
      <xsl:call-template name="wrapper">
        <xsl:with-param name="offset" select="$offset+string-length($token)+1"/>
        <xsl:with-param name="width" select="$width+string-length($token)+1"/>
      </xsl:call-template>
    </xsl:if>
    <xsl:if test="string-length($token)+$width+1>$text_width">
      <xsl:text>&#xA;  </xsl:text><xsl:value-of select="$token"/>
      <xsl:call-template name="wrapper">
        <xsl:with-param name="offset" select="$offset+string-length($token)+1"/>
        <xsl:with-param name="width" select="string-length($token)+2"/>
      </xsl:call-template>
    </xsl:if>
  </xsl:if>
</xsl:template>

</xsl:stylesheet>

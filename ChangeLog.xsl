<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text"/>

<xsl:template match="/">mp3unicode ChangeLog

<xsl:apply-templates/>
</xsl:template>

<xsl:template match="release">
<xsl:value-of select="date"/> -- Version <xsl:value-of select="version"/>
<xsl:apply-templates/>
<xsl:text>

</xsl:text>
</xsl:template>

<xsl:template match="change">
 * <xsl:value-of select="."/>
</xsl:template>

<xsl:template match="text()"/>

</xsl:stylesheet>
